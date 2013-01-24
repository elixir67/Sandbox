# coding:utf-8
import sys
from subprocess import Popen, PIPE, STDOUT
import re

# Configure settings
CCCMD = '"C:\Program Files (x86)\Code Collaborator Client\ccollab.exe" actionitems'
#CCCMD = '"C:\Program Files\Code Collaborator Client\ccollab.exe" actionitems'
CCSERVER = 'http://aim-cc:8080/go?page=ReviewDisplay&reviewid='

# Review #(ReviewId): "@(ChangeListId) - XXX"
action_item_pattern = re.compile(r'.+#(.+): "@(.+) - .+', re.I)

desc_pattern = re.compile(r'Description:', re.I)
files_pattern = re.compile(r'Files:', re.I)
review_by_pattern = re.compile(r'.+!!REVIEWED BY:', re.I)

def getreviewid(changelistid):
    p = Popen(CCCMD, shell=True, stdin=PIPE, stdout=PIPE, stderr=PIPE)
    count = 0
    reviewId = ''
    for line in p.stdout:
        id = getreviewidforline(line, changelistid)
        if id != '':
            count = count + 1
            reviewId = id
    # Print output and error message if any.
    for line in p.stdout:
        print line
    for line in p.stderr:
        print line
    if count == 1:
        print 'Changelist ' + changelistid + ' has review:' + reviewId
    elif count > 1:
        reviewId = ''
        print 'Changelist ' + changelistid + ' has more than one review!'
    else:
        reviewId = ''
        print 'Changelist ' + changelistid + ' has no review!'
    return reviewId

def getreviewidforline(line, changelistid):
    m = action_item_pattern.match(line)
    if m:
        clId = m.group(2)
        if clId == changelistid:
            reviewId = m.group(1)
            return reviewId
    return ''

def getreviewurl(changelistid) :
    id = getreviewid(changelistid)
    url = ''
    if id != '':
        url = CCSERVER+id
    else:
        print 'No valid URL found!'
    return url

def getdescription(changelistid, url):
    p4cmd = 'p4 change -o ' + changelistid
    p = Popen(p4cmd, shell=True, stdin=PIPE, stdout=PIPE, stderr=STDOUT )
    desc = ''
    isDesc = False
    hasReview = False
    for line in p.stdout:
        if not isDesc and desc_pattern.match(line):
            isDesc = True
        if isDesc and not hasReview:
            if review_by_pattern.match(line):
                hasReview = True
                print 'The review URL existed already in the changlist description!'
                desc = '' #reset it, it could save time without update description
                break;
            elif files_pattern.match(line):
                # Files section is coming.
                # Description section is done.
                # Let's append the review URL since it hasn't be found yet
                desc += '\t!!REVIEWED BY:' + url +'\n'
                isDesc = False
        desc += line
    return desc

def updatedescription(changelistid):
    url = getreviewurl(changelistid)
    if url != '':
        desc = getdescription(changelistid, url)
        if desc != '':
            p4cmd = 'p4 change -i '
            p = Popen(p4cmd, shell=True, stdin=PIPE, stdout=PIPE, stderr=PIPE)
            p.stdin.write(desc)
            p.stdin.close()
            # Print output and error message if any.
            for line in p.stdout:
                print line
            for line in p.stderr:
                print line
    else:
        print 'Code Review cannot be found!'

def showusage():
    print "Usage: python add_review_url.py changelistid"

if __name__ == '__main__':
    if (len(sys.argv) != 2):
        showusage()
    changelistid = sys.argv[1]
    print 'Update changelist ' + changelistid + ' description...'
    updatedescription(changelistid)
