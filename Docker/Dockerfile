FROM ubuntu:latest

RUN apt-get update && \
    apt-get install -y build-essential cmake qt5-default

COPY . /encode_decode

WORKDIR encode_decode/build

RUN cmake .. && make

ENTRYPOINT ["/encode_decode/build/encode_decode"]
