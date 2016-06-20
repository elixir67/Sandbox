#!/bin/bash
HOST=${1:-dlin@localhost}
PORT=${2:-22}
cat ~/.ssh/id_rsa.pub | ssh -p ${PORT} ${HOST} "cat >> ~/.ssh/authorized_keys"