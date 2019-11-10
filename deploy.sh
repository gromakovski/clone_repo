#!/bin/sh
cd $TRAVIS_BUILD_DIR/homework1/helloworld/build
ls -la
echo $TRAVIS_BUILD_DIR
echo $TRAVIS_BUILD_NUMBER
curl -T helloworld-0.0.$TRAVIS_BUILD_NUMBER-Linux.deb -:$BINTRAY_API_KEY ""

cd $TRAVIS_BUILD_DIR/homework2/build
curl -T ip_filter-0.0.$TRAVIS_BUILD_NUMBER-Linux.deb -:$BINTRAY_API_KEY ""

cd $TRAVIS_BUILD_DIR/homework3/build
curl -T allocator-0.0.$TRAVIS_BUILD_NUMBER-Linux.deb -:$BINTRAY_API_KEY ""

cd $TRAVIS_BUILD_DIR/homework4/build
curl -T print_ip-0.0.$TRAVIS_BUILD_NUMBER-Linux.deb -:$BINTRAY_API_KEY ""

cd $TRAVIS_BUILD_DIR/homework6/build
curl -T matrix-0.0.$TRAVIS_BUILD_NUMBER-Linux.deb -:$BINTRAY_API_KEY ""

cd $TRAVIS_BUILD_DIR/homework7/build
curl -T bulk-0.0.$TRAVIS_BUILD_NUMBER-Linux.deb -:$BINTRAY_API_KEY ""

cd $TRAVIS_BUILD_DIR/homework10/build
curl -T bulkmt-0.0.$TRAVIS_BUILD_NUMBER-Linux.deb -:$BINTRAY_API_KEY ""

cd $TRAVIS_BUILD_DIR/homework11/build
curl -T async-0.0.$TRAVIS_BUILD_NUMBER-Linux.deb -:$BINTRAY_API_KEY ""

cd $TRAVIS_BUILD_DIR/homework12/build
curl -T bulk_server-0.0.$TRAVIS_BUILD_NUMBER-Linux.deb -:$BINTRAY_API_KEY ""

# -curl -T helloworld-0.1.$TRAVIS_BUILD_NUMBER-Linux.deb -:$BINTRAY_API_KEY ""
