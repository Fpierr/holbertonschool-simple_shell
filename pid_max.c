#!/bin/bash

pid_max=$(cat /proc/sys/kernel/pid_max)
echo "la valeur maximale qu'un ID de processus peut avoir est: $pid_max"

