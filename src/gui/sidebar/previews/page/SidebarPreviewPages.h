/*
 * Xournal++
 *
 * Previews of the pages in the document
 *
 * @author Xournal++ Team
 * https://github.com/xournalpp/xournalpp
 *
 * @license GNU GPLv2 or later
 */

#pragma once

#include "gui/sidebar/previews/base/SidebarPreviewBase.h"

#include <XournalType.h>

class SidebarPreviewPages : public SidebarPreviewBase
{
public:
	SidebarPreviewPages(Control* control, GladeGui* gui, SidebarToolbar* toolbar);
	virtual ~SidebarPreviewPages();

public:
	/**
	 * Called when an action is performed
	 */
	void actionPerformed(SidebarActions action);

	/**
	 * @overwrite
	 */
	virtual string getName();

	/**
	 * @overwrite
	 */
	virtual string getIconName();

	/**
	 * Update the preview images
	 * @overwrite
	 */
	virtual void updatePreviews();

public:
	// DocumentListener interface (only the part which is not handled by SidebarPreviewBase)
	virtual void pageSizeChanged(size_t page);
	virtual void pageChanged(size_t page);
	virtual void pageSelected(size_t page);
	virtual void pageInserted(size_t page);
	virtual void pageDeleted(size_t page);

private:
	/**
	 * Unselect the last selected page, if any
	 */
	void unselectPage();

private:
	XOJ_TYPE_ATTRIB;

};
