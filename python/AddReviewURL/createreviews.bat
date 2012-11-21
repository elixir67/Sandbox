@echo
ccollab --pause-on-error --scm perforce --p4port %2 --p4user %3 --p4client "emptyArgumentPrefix %4 emptyArgumentSuffix" addchangelist new %1
c:\Python27\python.exe F:\GITHUB\Sandbox\python\AddReviewURL\add_review_url.py %1
