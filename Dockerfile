# Copyright 2019 Qwant Research. Licensed under the terms of the Apache 2.0 license. See LICENSE in the project root.

# FROM debian:9-slim
FROM ubuntu:19.04

LABEL maintainer="c.servan@qwantresearch.com"

ENV TZ=Europe/Paris
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

ENV LD_LIBRARY_PATH=/usr/local/lib

RUN apt-get -y update && \
    apt-get -y install \
        cmake \
        g++ \
        libboost-locale-dev \
        libboost-regex-dev \
        libyaml-cpp-dev \
	git \
	unzip \
	libprotobuf-dev \
	libprotoc-dev

ADD https://github.com/google/protobuf/releases/download/v3.6.1/protoc-3.6.1-linux-x86_64.zip /tmp/protoc-3.6.1-linux-x86_64.zip

RUN unzip /tmp/protoc-3.6.1-linux-x86_64.zip -d  /tmp/protoc-3.6.1/ && mv /tmp/protoc-3.6.1/bin/* /usr/local/bin/ && mv /tmp/protoc-3.6.1/include/* /usr/local/include/

COPY . /opt/qnlp-toolkit

WORKDIR /opt/qnlp-toolkit

RUN ./install.sh

RUN groupadd -r qnlp && useradd --system -s /bin/bash -g qnlp qnlp

USER qnlp 

