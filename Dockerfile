FROM debian:jessie-slim

MAINTAINER nirae

RUN apt-get -y update

RUN apt-get -y install build-essential valgrind bsdmainutils curl git-all

ENV APP_PATH /app

RUN mkdir -p APP_PATH && cd APP_PATH
WORKDIR $APP_PATH

CMD bash
