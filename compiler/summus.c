#include "ibscommon.h"
#include "ibsallocator.h"
#include "ibsdictionary.h"
#include "smmmsgs.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	for (int i = 1; i < argc; i++) {
		printf("%s\n", argv[i]);
	}

	PIbsAllocator a = ibsSimpleAllocatorCreate("test", 1024 * 1024);
	fputs("\nAllocator info after create: ", stdout);
	ibsSimpleAllocatorPrintInfo(a);
	
	void* testData = ibsAlloc(a, 4 * 1024 + 50);
	if (testData == NULL) assert(false);

	PIbsDict dict = ibsDictCreate(a);
	char val[] = "fsdfsa";
	char alsofound[] = "also found";
	char found[] = "found";
	char first[] = "first";
	char second[] = "second";

	ibsDictPut(dict, "asda", val);
	ibsDictPut(dict, "adsfssda", val);
	ibsDictPut(dict, "asgdsda", val);
	ibsDictPut(dict, "sdfgsasda", val);
	ibsDictPut(dict, "asdgfdsfa", alsofound);
	ibsDictPut(dict, "dfgajgfsda", val);
	ibsDictPut(dict, "xcvbxcasda", val);
	ibsDictPut(dict, "jkhdfgasda", found);
	ibsDictPut(dict, "jhgfcfasda", val);
	ibsDictPut(dict, "mnsbjasda", val);
	ibsDictPut(dict, "psdjhdfasda", val);
	ibsDictPut(dict, "uksflasda", val);

	ibsDictPush(dict, "PUSH", first);
	ibsDictPush(dict, "PUSH", second);

	char* firstPop = ibsDictPop(dict, "PUSH");
	char* secondPop = ibsDictPop(dict, "PUSH");
	char* elem1 = ibsDictGet(dict, "jkhdfgasda");
	char* elem2 = ibsDictGet(dict, "asdgfdsfa");

	printf("Pop first = %s\n", firstPop);
	printf("Pop second = %s\n", secondPop);
	printf("Get elem1 = %s\n", elem1);
	printf("Get elem2 = %s\n", elem2);

	struct SmmMsgs msgs = { 0 };
	msgs.a = a;
	struct SmmFilePos filePos = { "test", 12, 32 };
	smmPostGotBadReturnType(&msgs, filePos, "type1", "type2");
	filePos.lineNumber += 10;
	smmPostMessage(&msgs, errSmmCantAssignToConst, filePos);
	filePos.lineNumber -= 5;
	smmPostMessage(&msgs, errSmmNonConstInConstExpression, filePos);
	filePos.lineNumber -= 10;
	smmPostMessage(&msgs, errSmmFuncMustReturnValue, filePos);

	smmFlushMessages(&msgs);

	fputs("\nAllocator info after dict allocs: ", stdout);
	ibsSimpleAllocatorPrintInfo(a);

	ibsSimpleAllocatorReset(a);
	fputs("\nAllocator info after reset: ", stdout);
	ibsSimpleAllocatorPrintInfo(a);

	ibsSimpleAllocatorFree(a);

	return EXIT_SUCCESS;
}
