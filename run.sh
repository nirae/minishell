#! /bin/sh

docker run --name test_environment -ti -v $(pwd):/app --rm test_environment
