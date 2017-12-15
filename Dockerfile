ARG COMPILER

FROM registry.gitlab.com/offa/docker-images/${COMPILER}:stable

RUN apt-get install -y --no-install-recommends openssl libssl-dev valgrind && \
    mkdir deps && cd deps && \
    git clone --depth=1 https://github.com/cpputest/cpputest.git cpputest && \
    cd cpputest && mkdir _build && cd _build && \
    case ${CXX} in clang* ) export CXXFLAGS="-stdlib=libc++"; esac; \
    cmake -DC++11=ON -DTESTS=OFF .. && make && make install && \
    cd ../.. && \
    cd .. && rm -rf deps

