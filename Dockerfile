FROM ubuntu:latest

ARG DEBIAN_FRONTED=noninteractive
ENV TZ=Europe/Moscow

RUN apt-get update \
    && ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone \
    && apt-get install sudo -y \
    && apt-get install wget -y \
    && apt-get install lib32ncurses5-dev -y \
    && apt-get install lib32z1-dev \
    && dpkg-reconfigure -plow dash \
EXPOSE 22