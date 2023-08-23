FROM archlinux:latest

RUN pacman -Sy --noconfirm \
    base cmake ninja \
    git zip unzip curl tar wget \
    clang glibc pkg-config cppcheck llvm

RUN wget -O /usr/local/bin/lcov_cobertura https://raw.github.com/eriwen/lcov-to-cobertura-xml/master/lcov_cobertura/lcov_cobertura.py && \
    chmod +x /usr/local/bin/lcov_cobertura
