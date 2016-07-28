from elasticsearch import Elasticsearch
DOC_TYPE = 'logs'

FailedTransactionsCount = "failed_transactions_count"
PassedTransactionsCount = "passed_transactions_count"

es = Elasticsearch(
    [{'host': 'search-learn-perf-test-log-qwa3xherfbdkk4yo5blaa52enu.us-east-1.es.amazonaws.com', 'port': 80}])

idx = "logstash-perf_locust_logs"
id = "AVW0nJdnHtAZlxJ2bjNC"
doc_type = '%{[@metadata][type]}'


def print_document(index, type, id):
    res = es.get(index=index, doc_type=type, id=id)
    print(res)


def get_field_in_doc_count(index, doc_type, id, field):
    res = es.get(index=index, doc_type=doc_type, id=id)
    array = res['_source']['doc'][field]
    field_count = len(array)
    return field_count


def add_field(index, doc_type, id, field, value):
    doc = {
      'script': 'ctx._source.%s = %s' % (field, value)
    }
    res = es.update(index, doc_type, id, body=doc)
    print(res)


def remove_field(index, doc_type, id, field):
    doc = {
        'script': 'ctx._source.remove("'+field+'")'
    }
    res = es.update(index, doc_type, id, body=doc)
    print(res)


def search_all(index, doc_type):
    res = es.search(index=index, doc_type=doc_type, body={"query": {"match_all": {}}})
    print("%d documents found:" % res['hits']['total'])
    for doc in res['hits']['hits']:
        id = doc['_id']
        yield id


def add_fields(index, doc_type, doc_id):
    passed_count = get_field_in_doc_count(index, doc_type, doc_id, 'passed')
    failed_count = get_field_in_doc_count(index, doc_type, doc_id, 'failed')
    add_field(index, doc_type, doc_id, field=PassedTransactionsCount, value=passed_count)
    add_field(index, doc_type, doc_id, field=FailedTransactionsCount, value=failed_count)


def remove_fields(index, doc_type, doc_id):
    remove_field(index, doc_type, doc_id, field=PassedTransactionsCount)
    remove_field(index, doc_type, doc_id, field=FailedTransactionsCount)


def test_search():
    ids = search_all(idx, doc_type)
    lastId = -1
    for id in ids:
        print("ID: %s) " % id)
        # add_fields(idx, DOC_TYPE, id)
        lastId = id
        print_document(idx, doc_type, lastId)

test_search()
#print_document(idx, doc_type, '')
