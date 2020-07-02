#!/bin/bash

case `file $1` in
        *"gzip"*)
                echo GZip Datei;;
        *"ASCII"*)
                echo ASCII Datei;;
        *"tar"*)
                echo TAR Datei;;
esac

exit 0