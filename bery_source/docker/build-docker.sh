#!/usr/bin/env bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR/..

DOCKER_IMAGE=${DOCKER_IMAGE:-berylpay/beryld-develop}
DOCKER_TAG=${DOCKER_TAG:-latest}

BUILD_DIR=${BUILD_DIR:-.}

rm docker/bin/*
mkdir docker/bin
cp $BUILD_DIR/src/beryld docker/bin/
cp $BUILD_DIR/src/beryl-cli docker/bin/
cp $BUILD_DIR/src/beryl-tx docker/bin/
strip docker/bin/beryld
strip docker/bin/beryl-cli
strip docker/bin/beryl-tx

docker build --pull -t $DOCKER_IMAGE:$DOCKER_TAG -f docker/Dockerfile docker
