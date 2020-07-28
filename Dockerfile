# Copyright 2019 Qwant Research. Licensed under the terms of the Apache 2.0 license. See LICENSE in the project root.

FROM debian:9-slim

LABEL maintainer="c.servan@qwantresearch.com"

ENV TZ=Europe/Paris
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

ENV LD_LIBRARY_PATH=/usr/local/lib

RUN apt-get -y update && \
    apt-get -y install \
        cmake \
        g++ \
	sudo \
        libboost-locale-dev \
        libboost-regex-dev \
        libyaml-cpp-dev \
	git 

COPY . /opt/qnlp-toolkit

WORKDIR /opt/qnlp-toolkit

RUN ./install.sh

RUN groupadd -r qnlp && useradd --system -s /bin/bash -g qnlp qnlp

USER qnlp 
