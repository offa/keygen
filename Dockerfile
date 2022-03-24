ARG COMPILER

FROM registry.gitlab.com/offa/docker-images/${COMPILER}:stable

RUN apt-get update && \
    apt-get install -y --no-install-recommends openssl libssl-dev valgrind
