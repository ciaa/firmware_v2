#!/bin/bash
SCRIPT_DIR=$(dirname $(readlink -f $0))
BASE=$(readlink -f ${SCRIPT_DIR}/..)
LOG_FILE=${SCRIPT_DIR}/compilation.log
BRIEF_LOG=${SCRIPT_DIR}/brief.log

domake()
{
	make PROJECT=$1 all clean && echo "COMPILATION RESULT $1 PASS" || echo "COMPILATION RESULT $1 FAIL"
}

rm -f ${LOG_FILE}
SAPI_EX_PATH=$(echo ${BASE}/sapi_examples/*/*)
for d in ${SAPI_EX_PATH}
do
	p=${d##${BASE}/}
	echo Processing ${p} | tee -a ${LOG_FILE}
	(cd ${BASE} && domake ${p} |& tee -a ${LOG_FILE})
done
cat ${LOG_FILE} | grep "COMPILATION RESULT" > ${BRIEF_LOG}
