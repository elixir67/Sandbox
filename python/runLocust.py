import time
from optparse import OptionParser

import requests.packages.urllib3


def main():
    cli_parser = OptionParser(usage="usage: %prog")

    cli_parser.add_option("-L", "--locusturl",
                          type='string',
                          action="store",
                          dest="locust_url",
                          help="",
                          default='http://localhost:8089/')

    cli_parser.add_option("-c", "--clients",
                          type='int',
                          action="store",
                          dest="clients",
                          help="Total clients number to be simulated",
                          default=30)

    cli_parser.add_option("-r", "--hatch",
                          type='int',
                          action="store",
                          dest="hatch",
                          help="Hatch Rate",
                          default=3)

    cli_parser.add_option("-d", "--duration",
                          type='int',
                          action="store",
                          dest="duration",
                          help="Test time by minutes",
                          default=2)

    (options, args) = cli_parser.parse_args()

    locust_url=options.locust_url

    payload = {'locust_count': options.clients,
               'hatch_rate': options.hatch}

    swarm_url=locust_url+"swarm"
    r = requests.post(swarm_url, payload)

    print 'Start locust tests.'
    print 'Status code: %s' % r.status_code
    print 'Traceback: %s' % r.raise_for_status()
    print 'Wait %s minutes to stop.' % options.duration
    time.sleep(options.duration*60)

    stop_url=locust_url+'stop'
    r = requests.get(stop_url)

    print 'Stop locust tests.'
    print 'Status code: %s' % r.status_code
    print 'Traceback: %s' % r.raise_for_status()

if __name__ == "__main__":
    requests.packages.urllib3.disable_warnings()
    main()