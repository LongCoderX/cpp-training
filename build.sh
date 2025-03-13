#!/bin/zsh
function build() {
    if [ -d "build" ]; then
        rm -rf build
    fi
    cmake -S. -B build
    if [ $? -ne 0 ]; then
        echo "cmake failed"
        exit 1
    fi
    cmake --build build
    if [ $? -ne 0 ]; then
        echo "build failed"
        exit 1
    fi
    cmake --install build --prefix .
    if [ $? -ne 0 ]; then
        echo "install failed"
        exit 1
    fi
}

function clean() {
    if [ -d "build" ]; then
        rm -rf build
    fi

    if [ -d "include" ]; then
        rm -rf include    
    fi

    if [ -d "run" ]; then
        rm -rf run
    fi
}

case "$1" in
    build)
        build
        ;;
    clean)
        clean
        ;;
    *)
        echo "Usage: $0 {build|clean}"
        exit 1
        ;;
esac