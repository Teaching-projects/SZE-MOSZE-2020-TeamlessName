FROM ubuntu:20.04

RUN apt-get update && apt-get install --no-install-recommends -y \
  gcc g++ \
  cppcheck \
  valgrind \
&& rm -rf /var/lib/apt/lists/*
