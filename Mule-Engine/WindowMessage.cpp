#include "WindowMessage.h"
#include <ctime>
#include <unordered_set>

WindowMessage::WindowMessage(std::initializer_list<UINT> filters)
	:filters(filters)
{
}

std::wstring WindowMessage::operator()(UINT msg,WPARAM wparam, LPARAM lparam) const
{
	if (filters.size() != 0 && filters.find(msg) == filters.end())
		return std::wstring();

	auto range = msgMap.equal_range(msg);
	std::wstringstream ss;
	
	if (range.first == msgMap.end() && range.second == msgMap.end())
		ss << MakeMessage(L"Unknown msg #" + std::to_wstring(msg), wparam, lparam);
	else 
		for (auto it = range.first; it != range.second; ++it) 
			ss << MakeMessage(it->second, wparam, lparam);
	
	return ss.str();
}

std::wstring WindowMessage::MakeMessage(const std::wstring& strMsg, WPARAM wparam, LPARAM lparam) const
{
	constexpr int maxStrMsgSize = 30;
	std::wstringstream ss;

	ss << std::setfill(L' ') << std::left << std::setw(maxStrMsgSize) << strMsg;
	ss << L"WP: " << std::hex << std::showbase << std::setfill(L'0');
	ss << std::internal << std::setw(sizeof(WPARAM) * 2 + 2) << wparam << L'\t';
	ss << L"LP: " << std::hex << std::setw(sizeof(LPARAM) * 2 + 2) << lparam << std::endl;

	return ss.str();
}

const std::unordered_multimap<unsigned int, std::wstring> WindowMessage::msgMap = {
		RegisterMsg(WM_NULL),
		RegisterMsg(WM_CREATE),
		RegisterMsg(WM_DESTROY),
		RegisterMsg(WM_MOVE),
		RegisterMsg(WM_SIZE),
		RegisterMsg(WM_ACTIVATE),
		RegisterMsg(WM_SETFOCUS),
		RegisterMsg(WM_KILLFOCUS),
		RegisterMsg(WM_ENABLE),
		RegisterMsg(WM_SETREDRAW),
		RegisterMsg(WM_SETTEXT),
		RegisterMsg(WM_GETTEXT),
		RegisterMsg(WM_GETTEXTLENGTH),
		RegisterMsg(WM_PAINT),
		RegisterMsg(WM_CLOSE),
		RegisterMsg(WM_QUERYENDSESSION),
		RegisterMsg(WM_QUIT),
		RegisterMsg(WM_QUERYOPEN),
		RegisterMsg(WM_ERASEBKGND),
		RegisterMsg(WM_SYSCOLORCHANGE),
		RegisterMsg(WM_ENDSESSION),
		RegisterMsg(WM_SHOWWINDOW),
		RegisterMsg(WM_WININICHANGE),
		RegisterMsg(WM_DEVMODECHANGE),
		RegisterMsg(WM_ACTIVATEAPP),
		RegisterMsg(WM_FONTCHANGE),
		RegisterMsg(WM_TIMECHANGE),
		RegisterMsg(WM_CANCELMODE),
		RegisterMsg(WM_SETCURSOR),
		RegisterMsg(WM_MOUSEACTIVATE),
		RegisterMsg(WM_CHILDACTIVATE),
		RegisterMsg(WM_QUEUESYNC),
		RegisterMsg(WM_GETMINMAXINFO),
		RegisterMsg(WM_PAINTICON),
		RegisterMsg(WM_ICONERASEBKGND),
		RegisterMsg(WM_NEXTDLGCTL),
		RegisterMsg(WM_SPOOLERSTATUS),
		RegisterMsg(WM_DRAWITEM),
		RegisterMsg(WM_MEASUREITEM),
		RegisterMsg(WM_DELETEITEM),
		RegisterMsg(WM_VKEYTOITEM),
		RegisterMsg(WM_CHARTOITEM),
		RegisterMsg(WM_SETFONT),
		RegisterMsg(WM_GETFONT),
		RegisterMsg(WM_SETHOTKEY),
		RegisterMsg(WM_GETHOTKEY),
		RegisterMsg(WM_QUERYDRAGICON),
		RegisterMsg(WM_COMPAREITEM),
		RegisterMsg(WM_GETOBJECT),
		RegisterMsg(WM_COMPACTING),
		RegisterMsg(WM_COMMNOTIFY),
		RegisterMsg(WM_WINDOWPOSCHANGING),
		RegisterMsg(WM_WINDOWPOSCHANGED),
		RegisterMsg(WM_POWER),
		RegisterMsg(WM_COPYDATA),
		RegisterMsg(WM_CANCELJOURNAL),
		RegisterMsg(WM_NOTIFY),
		RegisterMsg(WM_INPUTLANGCHANGEREQUEST),
		RegisterMsg(WM_INPUTLANGCHANGE),
		RegisterMsg(WM_TCARD),
		RegisterMsg(WM_HELP),
		RegisterMsg(WM_USERCHANGED),
		RegisterMsg(WM_NOTIFYFORMAT),
		RegisterMsg(WM_CONTEXTMENU),
		RegisterMsg(WM_STYLECHANGING),
		RegisterMsg(WM_STYLECHANGED),
		RegisterMsg(WM_DISPLAYCHANGE),
		RegisterMsg(WM_GETICON),
		RegisterMsg(WM_SETICON),
		RegisterMsg(WM_NCCREATE),
		RegisterMsg(WM_NCDESTROY),
		RegisterMsg(WM_NCCALCSIZE),
		RegisterMsg(WM_NCHITTEST),
		RegisterMsg(WM_NCPAINT),
		RegisterMsg(WM_NCACTIVATE),
		RegisterMsg(WM_GETDLGCODE),
		RegisterMsg(WM_SYNCPAINT),
		RegisterMsg(WM_NCMOUSEMOVE),
		RegisterMsg(WM_NCLBUTTONDOWN),
		RegisterMsg(WM_NCLBUTTONUP),
		RegisterMsg(WM_NCLBUTTONDBLCLK),
		RegisterMsg(WM_NCRBUTTONDOWN),
		RegisterMsg(WM_NCRBUTTONUP),
		RegisterMsg(WM_NCRBUTTONDBLCLK),
		RegisterMsg(WM_NCMBUTTONDOWN),
		RegisterMsg(WM_NCMBUTTONUP),
		RegisterMsg(WM_NCMBUTTONDBLCLK),
		RegisterMsg(WM_NCXBUTTONDOWN),
		RegisterMsg(WM_NCXBUTTONUP),
		RegisterMsg(WM_NCXBUTTONDBLCLK),
		RegisterMsg(EM_GETSEL),
		RegisterMsg(EM_SETSEL),
		RegisterMsg(EM_GETRECT),
		RegisterMsg(EM_SETRECT),
		RegisterMsg(EM_SETRECTNP),
		RegisterMsg(EM_SCROLL),
		RegisterMsg(EM_LINESCROLL),
		RegisterMsg(EM_SCROLLCARET),
		RegisterMsg(EM_GETMODIFY),
		RegisterMsg(EM_SETMODIFY),
		RegisterMsg(EM_GETLINECOUNT),
		RegisterMsg(EM_LINEINDEX),
		RegisterMsg(EM_SETHANDLE),
		RegisterMsg(EM_GETHANDLE),
		RegisterMsg(EM_GETTHUMB),
		RegisterMsg(EM_LINELENGTH),
		RegisterMsg(EM_REPLACESEL),
		RegisterMsg(EM_GETLINE),
		RegisterMsg(EM_LIMITTEXT),
		RegisterMsg(EM_SETLIMITTEXT),
		RegisterMsg(EM_CANUNDO),
		RegisterMsg(EM_UNDO),
		RegisterMsg(EM_FMTLINES),
		RegisterMsg(EM_LINEFROMCHAR),
		RegisterMsg(EM_SETTABSTOPS),
		RegisterMsg(EM_SETPASSWORDCHAR),
		RegisterMsg(EM_EMPTYUNDOBUFFER),
		RegisterMsg(EM_GETFIRSTVISIBLELINE),
		RegisterMsg(EM_SETREADONLY),
		RegisterMsg(EM_SETWORDBREAKPROC),
		RegisterMsg(EM_GETWORDBREAKPROC),
		RegisterMsg(EM_GETPASSWORDCHAR),
		RegisterMsg(EM_SETMARGINS),
		RegisterMsg(EM_GETMARGINS),
		RegisterMsg(EM_GETLIMITTEXT),
		RegisterMsg(EM_POSFROMCHAR),
		RegisterMsg(EM_CHARFROMPOS),
		RegisterMsg(EM_SETIMESTATUS),
		RegisterMsg(EM_GETIMESTATUS),
		RegisterMsg(SBM_SETPOS),
		RegisterMsg(SBM_GETPOS),
		RegisterMsg(SBM_SETRANGE),
		RegisterMsg(SBM_GETRANGE),
		RegisterMsg(SBM_ENABLE_ARROWS),
		RegisterMsg(SBM_SETRANGEREDRAW),
		RegisterMsg(SBM_SETSCROLLINFO),
		RegisterMsg(SBM_GETSCROLLINFO),
		RegisterMsg(SBM_GETSCROLLBARINFO),
		RegisterMsg(BM_GETCHECK),
		RegisterMsg(BM_SETCHECK),
		RegisterMsg(BM_GETSTATE),
		RegisterMsg(BM_SETSTATE),
		RegisterMsg(BM_SETSTYLE),
		RegisterMsg(BM_CLICK),
		RegisterMsg(BM_GETIMAGE),
		RegisterMsg(BM_SETIMAGE),
		RegisterMsg(BM_SETDONTCLICK),
		RegisterMsg(WM_INPUT),
		RegisterMsg(WM_KEYDOWN),
		RegisterMsg(WM_KEYUP),
		RegisterMsg(WM_CHAR),
		RegisterMsg(WM_DEADCHAR),
		RegisterMsg(WM_SYSKEYDOWN),
		RegisterMsg(WM_SYSKEYUP),
		RegisterMsg(WM_SYSCHAR),
		RegisterMsg(WM_SYSDEADCHAR),
		RegisterMsg(WM_UNICHAR),
		RegisterMsg(WM_IME_STARTCOMPOSITION),
		RegisterMsg(WM_IME_ENDCOMPOSITION),
		RegisterMsg(WM_IME_COMPOSITION),
		RegisterMsg(WM_IME_KEYLAST),
		RegisterMsg(WM_INITDIALOG),
		RegisterMsg(WM_COMMAND),
		RegisterMsg(WM_SYSCOMMAND),
		RegisterMsg(WM_TIMER),
		RegisterMsg(WM_HSCROLL),
		RegisterMsg(WM_VSCROLL),
		RegisterMsg(WM_INITMENU),
		RegisterMsg(WM_INITMENUPOPUP),
		RegisterMsg(WM_MENUSELECT),
		RegisterMsg(WM_MENUCHAR),
		RegisterMsg(WM_ENTERIDLE),
		RegisterMsg(WM_MENURBUTTONUP),
		RegisterMsg(WM_MENUDRAG),
		RegisterMsg(WM_MENUGETOBJECT),
		RegisterMsg(WM_UNINITMENUPOPUP),
		RegisterMsg(WM_MENUCOMMAND),
		RegisterMsg(WM_CHANGEUISTATE),
		RegisterMsg(WM_UPDATEUISTATE),
		RegisterMsg(WM_QUERYUISTATE),
		RegisterMsg(WM_CTLCOLORMSGBOX),
		RegisterMsg(WM_CTLCOLOREDIT),
		RegisterMsg(WM_CTLCOLORLISTBOX),
		RegisterMsg(WM_CTLCOLORBTN),
		RegisterMsg(WM_CTLCOLORDLG),
		RegisterMsg(WM_CTLCOLORSCROLLBAR),
		RegisterMsg(WM_CTLCOLORSTATIC),
		RegisterMsg(CB_GETEDITSEL),
		RegisterMsg(CB_LIMITTEXT),
		RegisterMsg(CB_SETEDITSEL),
		RegisterMsg(CB_ADDSTRING),
		RegisterMsg(CB_DELETESTRING),
		RegisterMsg(CB_DIR),
		RegisterMsg(CB_GETCOUNT),
		RegisterMsg(CB_GETCURSEL),
		RegisterMsg(CB_GETLBTEXT),
		RegisterMsg(CB_GETLBTEXTLEN),
		RegisterMsg(CB_INSERTSTRING),
		RegisterMsg(CB_RESETCONTENT),
		RegisterMsg(CB_FINDSTRING),
		RegisterMsg(CB_SELECTSTRING),
		RegisterMsg(CB_SETCURSEL),
		RegisterMsg(CB_SHOWDROPDOWN),
		RegisterMsg(CB_GETITEMDATA),
		RegisterMsg(CB_SETITEMDATA),
		RegisterMsg(CB_GETDROPPEDCONTROLRECT),
		RegisterMsg(CB_SETITEMHEIGHT),
		RegisterMsg(CB_GETITEMHEIGHT),
		RegisterMsg(CB_SETEXTENDEDUI),
		RegisterMsg(CB_GETEXTENDEDUI),
		RegisterMsg(CB_GETDROPPEDSTATE),
		RegisterMsg(CB_FINDSTRINGEXACT),
		RegisterMsg(CB_SETLOCALE),
		RegisterMsg(CB_GETLOCALE),
		RegisterMsg(CB_GETTOPINDEX),
		RegisterMsg(CB_SETTOPINDEX),
		RegisterMsg(CB_GETHORIZONTALEXTENT),
		RegisterMsg(CB_SETHORIZONTALEXTENT),
		RegisterMsg(CB_GETDROPPEDWIDTH),
		RegisterMsg(CB_SETDROPPEDWIDTH),
		RegisterMsg(CB_INITSTORAGE),
		RegisterMsg(CB_GETCOMBOBOXINFO),
		RegisterMsg(CB_MSGMAX),
		RegisterMsg(WM_MOUSEMOVE),
		RegisterMsg(WM_LBUTTONDOWN),
		RegisterMsg(WM_LBUTTONUP),
		RegisterMsg(WM_LBUTTONDBLCLK),
		RegisterMsg(WM_RBUTTONDOWN),
		RegisterMsg(WM_RBUTTONUP),
		RegisterMsg(WM_RBUTTONDBLCLK),
		RegisterMsg(WM_MBUTTONDOWN),
		RegisterMsg(WM_MBUTTONUP),
		RegisterMsg(WM_MBUTTONDBLCLK),
		RegisterMsg(WM_MOUSEWHEEL),
		RegisterMsg(WM_XBUTTONDOWN),
		RegisterMsg(WM_XBUTTONUP),
		RegisterMsg(WM_XBUTTONDBLCLK),
		RegisterMsg(WM_MOUSEHWHEEL),
		RegisterMsg(WM_PARENTNOTIFY),
		RegisterMsg(WM_ENTERMENULOOP),
		RegisterMsg(WM_EXITMENULOOP),
		RegisterMsg(WM_NEXTMENU),
		RegisterMsg(WM_SIZING),
		RegisterMsg(WM_CAPTURECHANGED),
		RegisterMsg(WM_MOVING),
		RegisterMsg(WM_POWERBROADCAST),
		RegisterMsg(WM_DEVICECHANGE),
		RegisterMsg(WM_MDICREATE),
		RegisterMsg(WM_MDIDESTROY),
		RegisterMsg(WM_MDIACTIVATE),
		RegisterMsg(WM_MDIRESTORE),
		RegisterMsg(WM_MDINEXT),
		RegisterMsg(WM_MDIMAXIMIZE),
		RegisterMsg(WM_MDITILE),
		RegisterMsg(WM_MDICASCADE),
		RegisterMsg(WM_MDIICONARRANGE),
		RegisterMsg(WM_MDIGETACTIVE),
		RegisterMsg(WM_MDISETMENU),
		RegisterMsg(WM_ENTERSIZEMOVE),
		RegisterMsg(WM_EXITSIZEMOVE),
		RegisterMsg(WM_DROPFILES),
		RegisterMsg(WM_MDIREFRESHMENU),
		RegisterMsg(WM_IME_SETCONTEXT),
		RegisterMsg(WM_IME_NOTIFY),
		RegisterMsg(WM_IME_CONTROL),
		RegisterMsg(WM_IME_COMPOSITIONFULL),
		RegisterMsg(WM_IME_SELECT),
		RegisterMsg(WM_IME_CHAR),
		RegisterMsg(WM_IME_REQUEST),
		RegisterMsg(WM_IME_KEYDOWN),
		RegisterMsg(WM_IME_KEYUP),
		RegisterMsg(WM_NCMOUSEHOVER),
		RegisterMsg(WM_MOUSEHOVER),
		RegisterMsg(WM_NCMOUSELEAVE),
		RegisterMsg(WM_MOUSELEAVE),
		RegisterMsg(WM_CUT),
		RegisterMsg(WM_COPY),
		RegisterMsg(WM_PASTE),
		RegisterMsg(WM_CLEAR),
		RegisterMsg(WM_UNDO),
		RegisterMsg(WM_RENDERFORMAT),
		RegisterMsg(WM_RENDERALLFORMATS),
		RegisterMsg(WM_DESTROYCLIPBOARD),
		RegisterMsg(WM_DRAWCLIPBOARD),
		RegisterMsg(WM_PAINTCLIPBOARD),
		RegisterMsg(WM_VSCROLLCLIPBOARD),
		RegisterMsg(WM_SIZECLIPBOARD),
		RegisterMsg(WM_ASKCBFORMATNAME),
		RegisterMsg(WM_CHANGECBCHAIN),
		RegisterMsg(WM_HSCROLLCLIPBOARD),
		RegisterMsg(WM_QUERYNEWPALETTE),
		RegisterMsg(WM_PALETTEISCHANGING),
		RegisterMsg(WM_PALETTECHANGED),
		RegisterMsg(WM_HOTKEY),
		RegisterMsg(WM_PRINT),
		RegisterMsg(WM_PRINTCLIENT),
		RegisterMsg(WM_APPCOMMAND),
		RegisterMsg(WM_HANDHELDFIRST),
		RegisterMsg(WM_HANDHELDLAST),
		RegisterMsg(WM_AFXFIRST),
		RegisterMsg(WM_AFXLAST),
		RegisterMsg(WM_PENWINFIRST),
		RegisterMsg(WM_PENWINLAST),
		RegisterMsg(DM_GETDEFID),
		RegisterMsg(NIN_SELECT),
		RegisterMsg(WM_PSD_PAGESETUPDLG),
		RegisterMsg(WM_USER),
		RegisterMsg(DM_SETDEFID),
		RegisterMsg(WM_CHOOSEFONT_GETLOGFONT),
		RegisterMsg(WM_PSD_FULLPAGERECT),
		RegisterMsg(DM_REPOSITION),
		RegisterMsg(WM_PSD_MINMARGINRECT),
		RegisterMsg(WM_PSD_MARGINRECT),
		RegisterMsg(WM_PSD_GREEKTEXTRECT),
		RegisterMsg(WM_PSD_ENVSTAMPRECT),
		RegisterMsg(WM_PSD_YAFULLPAGERECT),
		RegisterMsg(CDM_FIRST),
		RegisterMsg(CDM_GETSPEC),
		RegisterMsg(CDM_GETFILEPATH),
		RegisterMsg(PSM_SETCURSEL),
		RegisterMsg(WM_CHOOSEFONT_SETLOGFONT),
		RegisterMsg(CDM_GETFOLDERPATH),
		RegisterMsg(PSM_REMOVEPAGE),
		RegisterMsg(WM_CHOOSEFONT_SETFLAGS),
		RegisterMsg(CDM_GETFOLDERIDLIST),
		RegisterMsg(PSM_ADDPAGE),
		RegisterMsg(CDM_SETCONTROLTEXT),
		RegisterMsg(PSM_CHANGED),
		RegisterMsg(CDM_HIDECONTROL),
		RegisterMsg(PSM_RESTARTWINDOWS),
		RegisterMsg(CDM_SETDEFEXT),
		RegisterMsg(PSM_REBOOTSYSTEM),
		RegisterMsg(PSM_CANCELTOCLOSE),
		RegisterMsg(PSM_QUERYSIBLINGS),
		RegisterMsg(PSM_UNCHANGED),
		RegisterMsg(PSM_APPLY),
		RegisterMsg(PSM_SETTITLEA),
		RegisterMsg(PSM_SETWIZBUTTONS),
		RegisterMsg(PSM_PRESSBUTTON),
		RegisterMsg(PSM_SETCURSELID),
		RegisterMsg(PSM_SETFINISHTEXTA),
		RegisterMsg(PSM_GETTABCONTROL),
		RegisterMsg(PSM_ISDIALOGMESSAGE),
		RegisterMsg(PSM_GETCURRENTPAGEHWND),
		RegisterMsg(PSM_INSERTPAGE),
		RegisterMsg(PSM_SETTITLEW),
		RegisterMsg(PSM_SETFINISHTEXTW),
		RegisterMsg(PSM_SETHEADERTITLEA),
		RegisterMsg(PSM_SETHEADERTITLEW),
		RegisterMsg(PSM_SETHEADERSUBTITLEA),
		RegisterMsg(PSM_SETHEADERSUBTITLEW),
		RegisterMsg(PSM_HWNDTOINDEX),
		RegisterMsg(PSM_INDEXTOHWND),
		RegisterMsg(PSM_PAGETOINDEX),
		RegisterMsg(PSM_INDEXTOPAGE),
		RegisterMsg(PSM_IDTOINDEX),
		RegisterMsg(PSM_INDEXTOID),
		RegisterMsg(PSM_GETRESULT),
		RegisterMsg(PSM_RECALCPAGESIZES),
		RegisterMsg(CDM_LAST),
		RegisterMsg(WM_APP)
};

std::wstring WindowMessage::FindDuplicates() const
{
	constexpr int maxStrMsgSize = 30;
	std::wstringstream ss;

	std::unordered_set<unsigned int> keys;

	// Iterate over all unique keys in the unordered_multimap
	for (const auto& pair : msgMap)
	{
		unsigned int key = pair.first;

		if (keys.find(key) != keys.end())
			continue;

		// Find the range of elements with the current key
		auto range = msgMap.equal_range(key);

		if (std::distance(range.first, range.second) <= 1)
			continue;

		ss << "Key: " << std::hex << std::showbase << key << std::endl;
		// Iterate over the range to access all values with the same key
		for (auto it = range.first; it != range.second; ++it) {
			std::wstring value = it->second;
			ss << "Value: " << value << std::endl;
		}

		keys.insert(key);
	}

	return ss.str();
}