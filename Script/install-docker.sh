#!/bin/bash

# install docker
wget -qO- https://get.docker.com/ | sh
sudo usermod -aG docker $(whoami)

# install docker-compose
# curl -L https://github.com/docker/compose/releases/download/1.7.1/docker-compose-`uname -s`-`uname -m` > /usr/local/bin/docker-compose
# chmod +x /usr/local/bin/docker-compose
# docker-compose --version

sudo apt-get -y install python-pip
sudo pip install docker-compose
