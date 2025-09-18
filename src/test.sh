#!/usr/bin/env bash

# Exit immediately if any command below fails.
set -e

make


echo "Generating a test_files directory.."
mkdir -p test_files
rm -f test_files/*


echo "Generating test files.."
printf "Hello, World!\n" > test_files/ascii.input
printf "Hello, World!" > test_files/ascii2.input
printf "Hello,\x00World!\n" > test_files/data.input
printf "" > test_files/empty.input
printf "ISO test: \xC6\xD8\xC5\n" > test_files/iso.input
printf "This is secret\n" > test_files/secretFile.input
chmod -r test_files/secretFile.input
yes "ABCDEFGHIJKLMNOPQRSTUVWXYZ" | head -n 100 > test_files/large_ascii.input
printf "     \n\t    \n" > test_files/whitespace.input
head -c 64 /dev/urandom > test_files/random.input
head -c 10 < /dev/zero > test_files/zeros.input
printf "\xFF\xFE\xFD\n" > test_files/highbit.input
### TODO: Generate more test files ###


echo "Running the tests.."
exitcode=0
for f in test_files/*.input
do
  echo ">>> Testing ${f}.."
  file    ${f} | sed -e 's/ASCII text.*/ASCII text/' \
                         -e 's/UTF-8 Unicode text.*/UTF-8 Unicode text/' \
                         -e 's/ISO-8859 text.*/ISO-8859 text/' \
                         -e 's/writable, regular file, no read permission/cannot determine (Permission denied)/' \
                         > "${f}.expected"
  ./file  "${f}" > "${f}.actual"

  if ! diff -u "${f}.expected" "${f}.actual"
  then
    echo ">>> Failed :-("
    exitcode=1
  else
    echo ">>> Success :-)"
  fi
done
exit $exitcode
