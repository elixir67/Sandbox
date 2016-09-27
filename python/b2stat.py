#!/usr/bin/env python
# coding=utf-8
#
# Copyright © 2015 Jacky Hu <hudayou@hotmail.com>
#

from __future__ import print_function

import argparse
import json
import sys

import pygal
import requests

from flask import Flask, request
app = Flask(__name__)


b2s = {
    'Visualization': '/webapps/visualization',
    'Ultra UI': '/webapps/ultraui',
    'Ultra': '/ultra',
    'Ultra Conversion': '/webapps/bb-ultra-conversion',
    'Task Progress': '/webapps/taskprogress',
    'Submission Services': '/webapps/submission-services',
    'Submission Provider Baboon': '/webapps/submission-provider-baboon',
    'Student Preview': '/webapps/spreview',
    'Stream Viewer': '/webapps/streamViewer',
    'Startup Baboon': '/webapps/startup-baboon',
    'Rubric': '/webapps/rubric',
    'Retention': '/webapps/retention',
    'Rest API': '/learn/api',
    'Portfolio': '/webapps/portfolio',
    'Portal': '/webapps/portal',
    'Plugins': '/webapps/plugins',
    'Offline Access': '/webapps/offline',
    'Mooc': [
        '/sso',
        '/signup',
        '/invitation',
        '/mooc-catalog',
        '/mooc-admin',
        '/webapps/item-analysis',
    ],
    'Grading': [
        '/webapps/inline-grading',
        '/webapps/gradebook',
    ],
    'Goal': '/webapps/goal',
    'Evidence Collection': '/webapps/evidenceCollection',
    'Enterprise Survey': '/webapps/enterpriseSurvey',
    'Date Management': '/webapps/date-management',
    'Data Integration': '/webapps/dataIntegration',
    'Crocodoc': '/webapps/crocodocdevkey',
    'Content Editor': '/webapps/vtbe-tinymce',
    'Cloud Storage Integration': '/webapps/cloudstorageintegration',
    'Kibana': '/kibana',
    'Caliper': '/webapps/caliper',
    'Calendar': '/webapps/calendar',
    # 'Core': '/webapps/blackboard',
    'CMS Admin': '/webapps/cmsadmin',
    'CMS': '/webapps/bbcms',
    'Assignment': '/webapps/assignment',
    'Api Gateway': '/webapps/api-gateway',
    'Discussion Board': '/webapps/discussionboard',
    'Achievements': '/webapps/achievements',
    'Blog Journals': '/webapps/blogs-journals',
    'Assessment': '/webapps/assessment',
    'Addressbook': [
        '/addressBook/manage',
        '/addressBook/add',
    ],
    'Admin': [
        '/checkUserNameExists',
        '/editUser',
        '/getAjaxNonce',
        '/selfCreateUser',
        '/selfCreateUserActionMappingInput',
        '/displayCreateUltraUser',
        '/exportLanguagePack',
        '/importLanguagePack',
        '/copyLanguagePack',
        '/languagePackManage',
        '/removeLanguagePack',
        '/manageScholarPlugins',
        '/copy_content',
        '/copy_exact',
        '/cp_copy_content',
        '/cp_copy_exact',
        '/contentExchange',
        '/moveFile',
        '/contentExchangeListImportLogFiles',
        '/displaySendCxLog',
        '/sendEmailCxLog',
        '/contentExchangeArchiveDelete',
        '/recycler',
        '/userManager',
        '/userEnrollment',
        '/viewDisclaimer',
        '/modifyLanguagePack',
        '/editLanguagePackResource',
        '/saveResourceEdit',
        '/manageLocale',
        '/displaySendLogs',
        '/displayDownloadLogs',
        '/displayLogsConfig',
        '/saveLogsConfig',
        '/displayLogsCourseCartridge',
        '/autoReporting',
        '/admin/avatarSettings',
        '/manageObserver',
        '/addObserver',
        '/removeObserver',
        '/admin/displaySystemTasks',
        '/launcher',
        '/getLicense',
        '/admin/emailContact',
        '/admin/systemInfo',
        '/admin/registrationInfo',
        '/admin/sessionFingerprintConfig',
        '/userCustomization/display',
        '/admin/learningSystemSettings/defaultDesignTemplate/manage',
        '/admin/diskQuota/manage',
        '/course/diskQuota/manage',
        '/admin/viList',
        '/admin/tools/settings',
        '/admin/tools/nodesettings',
        '/admin/learningSystemSettings/manageDefaultCourseMenu',
        '/admin/learningSystemSettings/addDesignTemplateItem',
        '/admin/learningSystemSettings/getDefaultCourseMenuContextMenu',
        '/admin/learningSystemSettings/doDefaultCourseMenuAction',
        '/admin/learningSystemSettings/repositionDesignTemplateItem',
        '/admin/learningSystemSettings/manageCourseImages',
        '/admin/learningSystemSettings/manageSystemIconTheme',
        '/bbConnectSync',
        '/admin/gradingSecuritySettings',
        '/admin/trialSiteConfig',
    ],
    'Announcement': [
        '/announcement',
        '/repositionAnnouncement',
    ],
    'Catalog': [
        '/catalogMgr',
        '/modifyCategory',
        '/viewCatalog',
    ],
    'Course Manager': [
        '/courseManager',
        '/categorizeCourse',
        '/editCourseManager',
        '/crossListCourse',
        '/separateOutCourse',
        '/courseEnrollment',
        '/enrollCourse',
        '/enrollAccept',
        '/editCourseEnrollment',
        '/courseMembership',
        '/course/tools/settings',
        '/course/addtoc',
        '/course/displayMenuInclude',
        '/course/previewStructure',
        '/course/menuFolderViewGenerator',
        '/course/courseMapPicker',
        '/course/getCPGradeCenterGroupItems',
        '/course/getCPGroupItems',
        '/course/getCourseFileItems',
        '/ddb',
        '/courseMain',
    ],
    # '/integration'
    # '/vi_modify'
    # '/templateOption'
    'Syllabus': [
        '/syllabus',
        '/modifyLesson',
    ],
    # '/reorderLessons'
    'Email': [
        '/displayEmail',
        '/sendEmail',
        '/myEmailTool',
        '/sendEmailLogs',
        '/sendEmailEnroll',
    ],
    'Domain': [
        '/domainManager',
        '/modifyDomain',
        '/domainAdmins',
        '/modifyDomainAdmin',
        '/domainCollections',
        '/courseCollCriteria',
        '/userCollCriteria',
        '/tabCollCriteria',
        '/moduleCollCriteria',
    ],
    'Role': [
        '/systemRoleManager',
        '/modifySystemRole',
        '/courseRoleManager',
        '/modifyCourseRole',
        '/managePrivileges',
    ],
    'Navigation': [
        '/navItemManager',
        '/modifyNavItem',
    ],
    'User Preference': [
        '/changePassword',
        '/userChangePassword',
        '/userPrivacy',
        '/personalSettings',
        '/myPlacesSettings',
        '/personalInfo',
    ],
    'Observer': [
        '/associateObserver',
        '/viewObservees',
        '/viewObserveeDetail',
        '/switchObservee',
    ],
    'Instrument Core': [
        '/deploymentResponse',
        '/instrumentcore/listPicker',
    ],
    'Work Context': [
        '/workcontext/picker',
    ],
    'Cartridge': [
        '/cartridgeAuth',
        '/cartridgeDownload',
    ],
    'Cp': [
        '/cp/courseProperties',
        '/cp/courseEnrollProperties',
        '/cp/manageCourseDesign',
        '/admin/learningSystemSettings/manageDefaultDesign',
    ],
    'Dynamic Menu': [
        '/navItemBasedDynamicMenuGenerator',
        '/modifyUserNavItemBasedContextMenuGenerator',
        '/modifyCourseNavItemBasedContextMenuGenerator',
        '/getCourseMenuContextMenu',
        '/courseInfoBasedContextMenuGenerator',
        '/manageNodeObjectMenuGenerator',
        '/course/coursemenu/repositionaction',
        '/course/coursemenu/coursecntrpaction',
        '/course/contentLink',
    ],
    'Page Banner': '/pageBanner',
    'Module Page': [
        '/modulepage/manageCourseModulePage',
        '/modulepage/view',
        '/modulepage/courseModulePageDisplayController',
        '/modulepage/repositionCourseModulePage',
        '/modulepage/viewGroup',
        '/modulepage/groupModulePageDisplayController',
        '/modulepage/repositionGroupModulePage',
    ],
    'Course Content': [
        '/manageQuickRule',
        '/manageMetadata',
        '/displayIndividualContent',
        '/displayLearningUnit',
        '/contentFolderView',
        '/manageCourseItem',
        '/content/removeItem',
        '/manageCourseItemPostProcessing',
        '/processTabContent',
        '/content/media',
        '/content/file',
        '/content/adaptiveReleaseRules',
        '/content/manageAdaptiveReleaseRule',
        '/content/adaptiveReleaseCriteria',
        '/content/manageCriteriaDate',
        '/content/manageCriteriaGradebook',
        '/content/manageCriteriaMembership',
        '/content/manageCriteriaReview',
        '/content/blankPage',
        '/doCourseMenuAction',
        '/manageLessonPlan',
        '/manageLearningUnit',
        '/learningUnitTocTreeViewGenerator',
        '/learningUnitStateSave',
    ],
    'Nautilus': [
        '/nautilus/nautilusMonitor',
        '/nautilus/viewHarness',
        '/nautilus/configureNotificationSettings',
        '/nautilus/configureGeneralSettings',
        '/nautilus/configureUserGeneralSettings',
        '/nautilus/configureUserNotificationSettings',
        '/nautilus/displayNotificationSettings',
        '/nautilus/notificationSettingsCaret',
        '/nautilus/notificationResponse',
        '/nautilus/notificationsLegend',
    ],
    'Group Space': [
        '/groupFileExchange',
        '/groupFileExchangeAdd',
        '/groupInventoryList',
        '/groupContentList',
        '/groupSignUp',
        '/groupSetSignUp',
        '/editGroup',
        '/editGroupEnrollment',
        '/group/getGroupMenuItems',
        '/groupSettings',
        '/module/groupModule',
        '/webapps/bb-group-mgmt-LEARN',
    ],
    'Task': [
        '/taskEditList',
        '/taskEdit',
        '/taskView',
    ],
    'Proxy Tool': [
        '/proxyLauncher',
        '/proxyCSS',
    ],
    'Links': [
        '/itemLinkController',
        '/toolLinkProperties',
        '/launchLink',
    ],
    # '/viewCalendar'
    'Glossary': [
        '/viewGlossary',
        '/importGlossary',
    ],
    'Batch': [
        '/showBatchResults',
        '/batchAddUsers',
        '/batchDeleteUsers',
        '/batchEnrollUsers',
        '/batchAddCourses',
        '/batchAddEnrollUsers',
    ],
    'Help': [
        '/viewExtendedHelp',
        '/viewDocumentation',
    ],
    'Roster': '/searchRoster',
    'Staff Info': [
        '/staffinfo/manageStaffInfo',
        '/staffinfo/reorderStaffInfo',
        '/staffinfo/staffInfoFolder',
        '/staffinfo/manageContacts',
    ],
    'Disk Usage': [
        '/diskUsage',
        '/includeCourseInNextDiskUsageReport',
    ],
    'Messaging': '/composeMessage',
    'Datasource': [
        '/dataSource/manager',
        '/dataSource/modify',
        '/dataSource/disablePurge',
    ],
    'Blti': [
        '/blti/manageToolProviders',
        '/blti/modifyProvider',
        '/blti/managePlacements',
        '/blti/modifyPlacement',
        '/blti/manageGlobalProperties',
        '/blti/launchLink',
        '/blti/launchPlacement',
        '/blti/launchFromGradeCenter',
        '/blti/launchReturn',
        '/blti/contentHandlerPlacement',
        '/blti/bulkLinkManager',
        '/blti/editLinkCredentials',
    ],
    # 'Data Integration': '/dataIntegration',
    'Authentication': [
        '/authentication/manager',
        '/authentication/createProvider',
        '/authentication/manager/logManager',
        '/authentication/reorderProviders',
        '/authentication/login',
    ],
    # '/enrollInviteeInCourse'
    'Insitutional Hierarchy': [
        '/institutionalHierarchy/manageHierarchy',
        '/institutionalHierarchy/manageObjects',
        '/institutionalHierarchy/displaySidebarAction',
        '/institutionalHierarchy/editNode',
        '/institutionalHierarchy/editNodeAdmin',
        '/institutionalHierarchy/nodeTreeViewGenerator',
        '/institutionalHierarchy/nodePicker',
        '/institutionalHierarchy/nodeSearch',
    ],
    # '/contextEncryption'
    # '/getCrossCourseMenuHTML'
    # '/navCourse'
    # '/getSystemTaskStatus'
    'Term': [
        '/manageTerms',
        '/viewTermCourses',
        '/editTerm',
        '/associateCoursesToTerm',
    ],
    # '/course/welcomePage'
    # '/setCourseTheme'
    # '/getCourseThemes'
    # '/getCourseStructures'
    # '/validateCourseThemes'
    # '/changeChild'
    # '/globalCourseNavMenuSection'
    'Security': [
        '/security/isolation/editIsolation',
        '/security/contentFilters',
        '/security/authenticationSettings',
    ],
    'IP Filter': '/ipFilterAction',
    'Internal Support': '/internalSupport',
    'Trial Site': '/trialSiteLandingPage',
}


def makeCondition(s):
    """ Make a condition from a string """
    if isinstance(s, list):
        c = None
        for v in s:
            if c is None:
                c = makeCondition(v)
            else:
                c += " or " + makeCondition(v)
        return c
    elif isinstance(s, basestring):
        return "pageUrl like '%" + s + "%'"
    else:
        return None


def makeQueries(d, t):
    """ Make a list of queries from a dict """
    def appendQuery(q, queries):
        if q is not None:
            q += " from PageView since " + t
            queries.append(q)
    aggregator = "filter(count(*), where {}) as '{}'"
    q = None
    queries = []
    maxQueryLength = 6000
    for k, v in d.iteritems():
        a = aggregator.format(makeCondition(v), k)
        if q is None:
            q = "select " + a
        else:
            if len(q+a) < maxQueryLength:
                q += ", " + a
            else:
                appendQuery(q, queries)
                q = None
    appendQuery(q, queries)
    return queries


def makeStats(accountId, queryKey, queries):
    """ Make stats with a list of queries """
    baseUrl = "https://insights-api.newrelic.com/v1/accounts/{}/query"
    url = baseUrl.format(accountId)
    headers = {
        "X-Query-Key": queryKey
    }
    labels = []
    counters = []
    for q in queries:
        params = {
            "nrql": q
        }
        response = requests.get(url, headers=headers, params=params)
        data = json.loads(response.text)
        labels.extend([c["alias"] for c in data["metadata"]["contents"]])
        counters.extend([r["count"] for r in data["results"]])

    return sorted(zip(labels, counters), key=lambda x: x[1], reverse=True)


def makeChart(accountId, queryKey, timeRange):
    """ Make a chart for an account with a query key across a time range """
    queries = makeQueries(b2s, timeRange)
    stats = makeStats(accountId, queryKey, queries)

    chart = pygal.Pie(
        truncate_legend=-1,
        truncate_label=-1,
    )
    chart.title = "b2 usage since " + timeRange
    for (k, v) in stats:
        print("%s,%s" % (k, v), file=sys.stderr)
        if v:
            chart.add(k, v)
    return chart


def makeArgParser():
    """
    Make a standard argument parser with arguments for talking to New Relic
    INSIGHTS

    -a accountId
    -q queryKey

    """
    parser = argparse.ArgumentParser(
        description='Standard Arguments for talking to New Relic INSIGHTS')

    subparser = parser.add_subparsers(dest='subcmd')
    serverSubparser = subparser.add_parser('server',
                                           help='Run in server mode')
    cmdlineSubparser = subparser.add_parser('cmdline',
                                            help='Run in command line mode')

    serverSubparser.set_defaults(server=True)
    cmdlineSubparser.set_defaults(server=False)

    cmdlineSubparser.add_argument('-a', '--accountId',
                                  action='store',
                                  required=True,
                                  help='New Relic account to connect to')

    cmdlineSubparser.add_argument('-q', '--queryKey',
                                  action='store',
                                  required=True,
                                  help='Query key for this account')

    cmdlineSubparser.add_argument('-t', '--timeRange',
                                  default='30 days ago',
                                  action='store',
                                  help='Time range across which to pull data')
    return parser


def makeArgs():
    """
    Supports the command-line arguments needed for New Relic INSIGHTS
    """
    parser = makeArgParser()
    args = parser.parse_args()
    return args


def main():
    args = makeArgs()
    if args.server:
        app.run()
    else:
        chart = makeChart(args.accountId, args.queryKey, args.timeRange)
        chart.render_in_browser()


@app.route('/charts/pie')
def pie_route():
    args = request.args
    chart = makeChart(args["accountId"], args["queryKey"], args["timeRange"])
    return chart.render_response()

if __name__ == '__main__':
    main()
