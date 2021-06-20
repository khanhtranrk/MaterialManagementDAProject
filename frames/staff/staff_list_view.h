#ifndef __FRAMES_STAFF_STAFF_LIST_VIEW__
#define __FRAMES_STAFF_STAFF_LIST_VIEW__

#ifdef __cplusplus
extern "C" {
#endif

// Render Header
void STPRenderStaffListViewHeader(ListView list_view) {
  position_tp position_x = list_view->position_x;
  position_tp position_y = list_view->position_y;
  color_tp foreground = PROGRAM_FOREGROUND;
  color_tp background = PROGRAM_BACKGROUND_LV1;

  DrawRecShape(
    list_view->width, 1,
    ' ',
    position_x, position_y,
    foreground, background
  );

  WriteStr("Mã", position_x + 2, position_y, foreground, background);
  WriteStr("Tên", position_x + 14, position_y, foreground, background);
  WriteStr("Họ", position_x + 48, position_y, foreground, background);
  WriteStr("Giới tính", position_x + 82, position_y, foreground, background);
}

// Render Footer
void STPRenderStaffListViewFooter(ListView list_view, int page) {
  position_tp position_x = list_view->position_x;
  position_tp position_y = list_view->position_y + list_view->height - 1;
  color_tp foreground = PROGRAM_FOREGROUND;
  color_tp background = PROGRAM_BACKGROUND_LV1;

  int staff_list_count = StaffListCount(archive->staff_list);
  int total_page = staff_list_count / ((list_view->height - 2) / list_view->item_context->height);
  if (staff_list_count % ((list_view->height - 2) / list_view->item_context->height) != 0)
    total_page ++;

  DrawRecShape(
    list_view->width, 1,
    ' ',
    position_x, position_y,
    foreground, background
  );

  WriteStr("Tổng số: ", position_x + 2, position_y, foreground, background);
  WriteInt(staff_list_count, CURSOR_POSITION_X, CURSOR_POSITION_Y, foreground, background);
  WriteStr("Trang: ", list_view->position_x + 72, CURSOR_POSITION_Y, foreground, background);
  WriteInt(page + 1, CURSOR_POSITION_X, CURSOR_POSITION_Y, foreground, background);
  WriteChar('/', CURSOR_POSITION_X, CURSOR_POSITION_Y, foreground, background);
  WriteInt(total_page, CURSOR_POSITION_X, CURSOR_POSITION_Y, foreground, background);
}

void RenderStaffListView(ListView list_view, int page) {
  // Header
  STPRenderStaffListViewHeader(list_view);

  // List (exclude header and footer)
  list_view->position_y ++;
  list_view->height -= 2;
  int limit = (list_view->height / list_view->item_context->height);
  TakeStaffsInArchive(list_view->linear_list, page * limit, limit);
  RenderListView(list_view);
  list_view->position_y --;
  list_view->height += 2;

  // Footer
  STPRenderStaffListViewFooter(list_view, page);
}

void STPUpdatePageOnStaffListViewFooter(ListView list_view, int page, int total_page) {
  WriteInt(page + 1, list_view->position_x + 79, list_view->position_y + list_view->height, PROGRAM_FOREGROUND, PROGRAM_BACKGROUND_LV1);
  WriteChar('/', CURSOR_POSITION_X, CURSOR_POSITION_Y, PROGRAM_FOREGROUND, PROGRAM_BACKGROUND_LV1);
  WriteInt(total_page, CURSOR_POSITION_X, CURSOR_POSITION_Y, PROGRAM_FOREGROUND, PROGRAM_BACKGROUND_LV1);
}

void STPStaffListViewTurnToPage(ListView list_view, int limit, int page, int total_page) {
  TakeStaffsInArchive(list_view->linear_list, page * limit, limit);
  STPUpdatePageOnStaffListViewFooter(list_view, page, total_page);
  RenderListView(list_view);
}

keycode_tp ActiveStaffListView(ListView list_view, int &page) {
  if (StaffListCount(archive->staff_list) == 0)
    return KEY_UP;

  list_view->position_y ++;
  list_view->height -= 2;

  int staff_list_count = StaffListCount(archive->staff_list);
  int total_page = staff_list_count / (list_view->height / list_view->item_context->height);
  if (staff_list_count % (list_view->height / list_view->item_context->height) != 0)
    total_page ++;
  int limit = (list_view->height / list_view->item_context->height);

  keycode_tp keycode;
  do {
    keycode = ActiveListViewStraight(list_view);

    if (keycode == KEY_UP) {
      if (page == 0) break;
      page --;
      STPStaffListViewTurnToPage(list_view, limit, page, total_page);
      list_view->selected_item = list_view->linear_list->count - 1;
    } else if (keycode == KEY_DOWN) {
      if ((page + 1) * limit >= staff_list_count) continue;
      page ++;
      STPStaffListViewTurnToPage(list_view, limit, page, total_page);
      list_view->selected_item = 0;
    } else if (keycode == KEY_LEFT) {
      if (page == 0) {
        keycode = NULL_KEY;
        continue;
      }

      page --;
      STPStaffListViewTurnToPage(list_view, limit, page, total_page);
    } else if (keycode == KEY_RIGHT) {
      if ((page + 1) * limit >= staff_list_count) {
        keycode = NULL_KEY;
        continue;
      }

      page ++;
      STPStaffListViewTurnToPage(list_view, limit, page, total_page);
    }
  } while (!list_view->console(keycode));

  list_view->position_y --;
  list_view->height += 2;
  return keycode;
}

/* includes */

// #include "list_view.cpp"

#ifdef __cplusplus
}
#endif

#endif
