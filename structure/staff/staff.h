/* staff */

#ifndef __STRUCTURE_STAFF__
#define __STRUCTURE_STAFF__

#include <stdlib.h>
#include <string.h>

#include "../../support/message/message.h"
#include "../invoice/invoice.h"

#define STAFF_CODE_MAX_LEN 10
#define STAFF_FIRST_NAME_MAX_LEN 32
#define STAFF_LAST_NAME_MAX_LEN 64
#define STAFF_LIST_MAX_ITEMS 500

#define STAFF_SEX_FEMALE 'F'
#define STAFF_SEX_MALE 'M'

#define STAFF_CODE_DEFAULT_VALUE "\0"
#define STAFF_FIRST_NAME_DEFUALT_VALUE "\0"
#define STAFF_LAST_NAME_DEFAULT_VALUE "\0"
#define STAFF_SEX_DEFAULT_VALUE STAFF_SEX_FEMALE
#define STAFF_INVOICES_DEFAULT_VALUE NewInvoiceList()

#define STAFF_SHOW_FORMAT_DEFAULT "%-12s %-24s %-24s %c\n"
#define STAFF_LIST_SHOW_FORMAT_DEFAULT "%-12s %-24s %-24s %c\n"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct StaffT {
  char code[STAFF_CODE_MAX_LEN];
  char first_name[STAFF_LAST_NAME_MAX_LEN];
  char last_name[STAFF_FIRST_NAME_MAX_LEN];
  char sex;
  InvoiceList invoices;
} StaffT, * Staff;

typedef struct StaffListT {
  int count;
  StaffT * staffs[STAFF_LIST_MAX_ITEMS];
} StaffListT, * StaffList;

/* Object methods */

Staff NewStaff(const char *, const char *, const char *, char, InvoiceList);
void DestroyStaff(Staff &);
void RevokeStaff(Staff &);

void ReplaceStaff(Staff &, Staff);
void TranferStaff(Staff, Staff &);
void CopyStaff(Staff, Staff);
Staff DuplicateStaff(Staff);

/* List methods */

// New and Destroy
StaffList NewStaffList();
void DestroyStaffList(StaffList &);

// Logic
bool IsStaffListEmpty(StaffList);
bool IsStaffListListFull(StaffList);
bool IsCodeInStaffList(StaffList, const char *);
bool IsInStaffList(StaffList, Staff);

// Insert
message_tp AddItemToStaffList(StaffList &, Staff);
message_tp InsertItemToBeginningOfStaffList(StaffList &, Staff);
message_tp InsertItemToEndOfStaffList(StaffList &, Staff);
message_tp InsertItemToStaffListByIndex(StaffList &, Staff, int);

// Update
message_tp UpdateItemInStaffList(StaffList, Staff);

// Get
Staff GetFirstItemInStaffList(StaffList);
Staff GetLastItemInStaffList(StaffList);
Staff GetStaffInListByIndex(StaffList, int);
Staff GetStaffInListByCode(StaffList, const char *);

// Delete
message_tp DeleteFirstItemInStaffList(StaffList &);
message_tp DeleteLastItemInStaffList(StaffList &);
message_tp DeleteItemInStaffListByIndex(StaffList &, int);
message_tp DeleteItemInStaffListByCode(StaffList &, const char *);
message_tp DeleteItemInStaffList(StaffList &, Staff);

// Test
void StaffListEach(StaffList, void (* perform) (Staff));
void ShowStaff(Staff, const char *);
void ShowStaffList(StaffList, const char *);

#include "staff.cpp"

#ifdef __cplusplus
}
#endif

#endif