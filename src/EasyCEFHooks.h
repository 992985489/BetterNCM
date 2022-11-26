#pragma once
#include "detours/detours.h"
#include "include/cef_v8.h"
#include "include/cef_app.h"
#include "include/cef_browser.h"
#include "pystring/pystring.h"
#include "include/capi/cef_client_capi.h"
#include "include/capi/cef_app_capi.h"
#include "include/capi/cef_zip_reader_capi.h"
#include "include/internal/cef_export.h"
#include "include/capi/cef_v8_capi.h"
#include "utils.h"
#include "shellapi.h"
#include <string>
using namespace std;


class EasyCEFHooks
{
	static _cef_frame_t* frame;
	static cef_v8context_t* contextl;

	static struct _cef_client_t* cef_client;
	static PVOID origin_cef_browser_host_create_browser;
	static PVOID origin_cef_initialize;
	static PVOID origin_cef_get_keyboard_handler;
	static PVOID origin_cef_load_handler;
	static PVOID origin_cef_on_load_start;
	static PVOID origin_cef_on_key_event;
	static PVOID origin_cef_v8context_get_current_context;
	static PVOID origin_cef_zip_reader_create;
	static PVOID origin_on_before_command_line_processing;
	static PVOID origin_command_line_append_switch;
<<<<<<< Updated upstream
	static PVOID origin_cef_register_scheme_handler_factory;
	static PVOID origin_cef_scheme_handler_create;
=======
	static PVOID origin_cef_zip_reader_read_file;

	static int CEF_CALLBACK hook_cef_zip_reader_read_file(struct _cef_zip_reader_t* self,
		void* buffer,
		size_t bufferSize);

	static cef_zip_reader_t* hook_cef_zip_reader_create(
		struct _cef_stream_reader_t* stream);
>>>>>>> Stashed changes

	static cef_v8context_t* hook_cef_v8context_get_current_context();

	static int CEF_CALLBACK hook_cef_on_key_event(struct _cef_keyboard_handler_t* self,
		struct _cef_browser_t* browser,
		const struct _cef_key_event_t* event,
		cef_event_handle_t os_event);
	static _cef_keyboard_handler_t* CEF_CALLBACK hook_cef_get_keyboard_handler(struct _cef_client_t* self);

	static int CEF_CALLBACK read(struct _cef_resource_handler_t* self,
		void* data_out,
		int bytes_to_read,
		int* bytes_read,
		struct _cef_resource_read_callback_t* callback);

	static _cef_load_handler_t* CEF_CALLBACK hook_cef_load_handler(struct _cef_client_t* self);
	static void CEF_CALLBACK hook_cef_on_load_start(struct _cef_load_handler_t* self,
		struct _cef_browser_t* browser,
		struct _cef_frame_t* frame,
		cef_transition_type_t transition_type);

	static _cef_resource_handler_t* CEF_CALLBACK hook_cef_scheme_handler_create(
		struct _cef_scheme_handler_factory_t* self,
		struct _cef_browser_t* browser,
		struct _cef_frame_t* frame,
		const cef_string_t* scheme_name,
		struct _cef_request_t* request);

	static int hook_cef_register_scheme_handler_factory(
		const cef_string_t* scheme_name,
		const cef_string_t* domain_name,
		cef_scheme_handler_factory_t* factory);

	static void CEF_CALLBACK get_response_headers(struct _cef_resource_handler_t* self,
		struct _cef_response_t* response,
		int64* response_length,
		cef_string_t* redirectUrl);

	static int hook_cef_browser_host_create_browser(
		const cef_window_info_t* windowInfo,
		struct _cef_client_t* client,
		const cef_string_t* url,
		const struct _cef_browser_settings_t* settings,
		struct _cef_request_context_t* request_context);

	static int hook_cef_initialize(const struct _cef_main_args_t* args,
		const struct _cef_settings_t* settings,
		cef_app_t* application,
		void* windows_sandbox_info);

	static void CEF_CALLBACK hook_on_before_command_line_processing(
		struct _cef_app_t* self,
		const cef_string_t* process_type,
		struct _cef_command_line_t* command_line);

	static void CEF_CALLBACK hook_command_line_append_switch(_cef_command_line_t* self, const cef_string_t* name);
public:
	static bool InstallHooks();
	static bool UninstallHook();
	static void executeJavaScript(_cef_frame_t* frame, string script, string url = "libeasycef/injext.js");
	static std::function<void(_cef_client_t*, struct _cef_browser_t*, const struct _cef_key_event_t*)> onKeyEvent;
	static std::function<void(struct _cef_browser_t* browser, struct _cef_frame_t* frame, cef_transition_type_t transition_type)> onLoadStart;
	static std::function<bool(string)> onAddCommandLine;
};

