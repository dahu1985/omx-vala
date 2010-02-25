/* simple-mp3-player.c generated by valac, the Vala compiler
 * generated from simple-mp3-player.vala, do not modify */


#include <glib.h>
#include <glib-object.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <OMX_Core.h>
#include <OMX_Component.h>
#include <omx-util.h>
#include <bellagio/tsemaphore.h>

#define _g_error_free0(var) ((var == NULL) ? NULL : (var = (g_error_free (var), NULL)))
#define _fclose0(var) ((var == NULL) ? NULL : (var = (fclose (var), NULL)))


extern FILE* fd;
FILE* fd = NULL;
extern OMX_HANDLETYPE audiodec_handle;
extern OMX_HANDLETYPE audiosink_handle;
OMX_HANDLETYPE audiodec_handle = NULL;
OMX_HANDLETYPE audiosink_handle = NULL;
extern OMX_BUFFERHEADERTYPE** in_buffer_audiosink;
extern gint in_buffer_audiosink_length1;
OMX_BUFFERHEADERTYPE** in_buffer_audiosink = NULL;
gint in_buffer_audiosink_length1 = 0;
static gint in_buffer_audiosink_size = 0;
extern OMX_BUFFERHEADERTYPE** in_buffer_audiodec;
extern gint in_buffer_audiodec_length1;
OMX_BUFFERHEADERTYPE** in_buffer_audiodec = NULL;
gint in_buffer_audiodec_length1 = 0;
static gint in_buffer_audiodec_size = 0;
extern OMX_BUFFERHEADERTYPE** out_buffer_audiodec;
extern gint out_buffer_audiodec_length1;
OMX_BUFFERHEADERTYPE** out_buffer_audiodec = NULL;
gint out_buffer_audiodec_length1 = 0;
static gint out_buffer_audiodec_size = 0;
extern tsem_t audiodec_sem;
tsem_t audiodec_sem = {0};
extern tsem_t audiosink_sem;
tsem_t audiosink_sem = {0};
extern tsem_t eos_sem;
tsem_t eos_sem = {0};

void play (const char* filename, GError** error);
gint _main (char** args, int args_length1);
void get_handles (GError** error);
void handle_print_info (const char* name, OMX_HANDLETYPE handle, GError** error);
void change_state_to (OMX_STATETYPE state, GError** error);
void allocate_buffers (GError** error);
void wait_for_change_of_state (void);
void move_buffers (GError** error);
void wait_for_eos (void);
void free_buffers (GError** error);
void free_handles (GError** error);
OMX_ERRORTYPE audiodec_event_handler (OMX_HANDLETYPE component, OMX_EVENTTYPE event, guint32 data1, guint32 data2);
static OMX_ERRORTYPE _audiodec_event_handler_omx_event_handler_func (OMX_HANDLETYPE component, gpointer self, OMX_EVENTTYPE event, guint32 data1, guint32 data2, void* event_data);
OMX_ERRORTYPE audiodec_empty_buffer_done (OMX_HANDLETYPE component, OMX_BUFFERHEADERTYPE* buffer);
static OMX_ERRORTYPE _audiodec_empty_buffer_done_omx_empty_buffer_done_func (OMX_HANDLETYPE component, gpointer self, OMX_BUFFERHEADERTYPE* buffer);
OMX_ERRORTYPE audiodec_fill_buffer_done (OMX_HANDLETYPE component, OMX_BUFFERHEADERTYPE* buffer);
static OMX_ERRORTYPE _audiodec_fill_buffer_done_omx_fill_buffer_done_func (OMX_HANDLETYPE component, gpointer self, OMX_BUFFERHEADERTYPE* buffer);
OMX_ERRORTYPE audiosink_event_handler (OMX_HANDLETYPE component, OMX_EVENTTYPE event, guint32 data1, guint32 data2);
static OMX_ERRORTYPE _audiosink_event_handler_omx_event_handler_func (OMX_HANDLETYPE component, gpointer self, OMX_EVENTTYPE event, guint32 data1, guint32 data2, void* event_data);
OMX_ERRORTYPE audiosink_empty_buffer_done (OMX_HANDLETYPE component, OMX_BUFFERHEADERTYPE* buffer);
static OMX_ERRORTYPE _audiosink_empty_buffer_done_omx_empty_buffer_done_func (OMX_HANDLETYPE component, gpointer self, OMX_BUFFERHEADERTYPE* buffer);
#define AUDIODEC_COMPONENT_NAME "OMX.st.audio_decoder.mp3.mad"
#define AUDIOSINK_COMPONENT_NAME "OMX.st.alsa.alsasink"
#define N_BUFFERS 2
#define BUFFER_OUT_SIZE 32768
#define BUFFER_IN_SIZE 4096
void read_buffer_from_fd (OMX_BUFFERHEADERTYPE* buffer);

const OMX_CALLBACKTYPE audiodec_callbacks = {_audiodec_event_handler_omx_event_handler_func, _audiodec_empty_buffer_done_omx_empty_buffer_done_func, _audiodec_fill_buffer_done_omx_fill_buffer_done_func};
const OMX_CALLBACKTYPE audiosink_callbacks = {_audiosink_event_handler_omx_event_handler_func, _audiosink_empty_buffer_done_omx_empty_buffer_done_func, NULL};


gint _main (char** args, int args_length1) {
	gint result;
	GError * _inner_error_;
	_inner_error_ = NULL;
	if (args_length1 != 2) {
		g_print ("%s <file.mp3>\n", args[0]);
		result = 1;
		return result;
	}
	{
		play (args[1], &_inner_error_);
		if (_inner_error_ != NULL) {
			goto __catch0_g_error;
		}
		result = 0;
		return result;
	}
	goto __finally0;
	__catch0_g_error:
	{
		GError * e;
		e = _inner_error_;
		_inner_error_ = NULL;
		{
			g_print ("%s\n", e->message);
			result = 1;
			_g_error_free0 (e);
			return result;
		}
	}
	__finally0:
	if (_inner_error_ != NULL) {
		g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
		g_clear_error (&_inner_error_);
		return 0;
	}
}


int main (int argc, char ** argv) {
	g_type_init ();
	return _main (argv, argc);
}


static GQuark omx_error_domain (void) {
	GQuark result;
	result = g_quark_from_string ("Omx.Error");
	return result;
}


static const char* omx_error_to_string (OMX_ERRORTYPE self) {
	const char* result;
	switch (self) {
		case OMX_ErrorNone:
		{
			result = "Omx.Error.None";
			return result;
		}
		case OMX_ErrorInsufficientResources:
		{
			result = "Omx.Error.InsufficientResources";
			return result;
		}
		case OMX_ErrorUndefined:
		{
			result = "Omx.Error.Undefined";
			return result;
		}
		case OMX_ErrorInvalidComponentName:
		{
			result = "Omx.Error.InvalidComponentName";
			return result;
		}
		case OMX_ErrorComponentNotFound:
		{
			result = "Omx.Error.ComponentNotFound";
			return result;
		}
		case OMX_ErrorInvalidComponent:
		{
			result = "Omx.Error.InvalidComponent";
			return result;
		}
		case OMX_ErrorBadParameter:
		{
			result = "Omx.Error.BadParameter";
			return result;
		}
		case OMX_ErrorNotImplemented:
		{
			result = "Omx.Error.NotImplemented";
			return result;
		}
		case OMX_ErrorUnderflow:
		{
			result = "Omx.Error.Underflow";
			return result;
		}
		case OMX_ErrorOverflow:
		{
			result = "Omx.Error.Overflow";
			return result;
		}
		case OMX_ErrorHardware:
		{
			result = "Omx.Error.Hardware";
			return result;
		}
		case OMX_ErrorInvalidState:
		{
			result = "Omx.Error.InvalidState";
			return result;
		}
		case OMX_ErrorStreamCorrupt:
		{
			result = "Omx.Error.StreamCorrupt";
			return result;
		}
		case OMX_ErrorPortsNotCompatible:
		{
			result = "Omx.Error.PortsNotCompatible";
			return result;
		}
		case OMX_ErrorResourcesLost:
		{
			result = "Omx.Error.ResourcesLost";
			return result;
		}
		case OMX_ErrorNoMore:
		{
			result = "Omx.Error.NoMore";
			return result;
		}
		case OMX_ErrorVersionMismatch:
		{
			result = "Omx.Error.VersionMismatch";
			return result;
		}
		case OMX_ErrorNotReady:
		{
			result = "Omx.Error.NotReady";
			return result;
		}
		case OMX_ErrorTimeout:
		{
			result = "Omx.Error.Timeout";
			return result;
		}
		case OMX_ErrorSameState:
		{
			result = "Omx.Error.SameState";
			return result;
		}
		case OMX_ErrorResourcesPreempted:
		{
			result = "Omx.Error.ResourcesPreempted";
			return result;
		}
		case OMX_ErrorPortUnresponsiveDuringAllocation:
		{
			result = "Omx.Error.PortUnresponsiveDuringAllocation";
			return result;
		}
		case OMX_ErrorPortUnresponsiveDuringDeallocation:
		{
			result = "Omx.Error.PortUnresponsiveDuringDeallocation";
			return result;
		}
		case OMX_ErrorPortUnresponsiveDuringStop:
		{
			result = "Omx.Error.PortUnresponsiveDuringStop";
			return result;
		}
		case OMX_ErrorIncorrectStateTransition:
		{
			result = "Omx.Error.IncorrectStateTransition";
			return result;
		}
		case OMX_ErrorIncorrectStateOperation:
		{
			result = "Omx.Error.IncorrectStateOperation";
			return result;
		}
		case OMX_ErrorUnsupportedSetting:
		{
			result = "Omx.Error.UnsupportedSetting";
			return result;
		}
		case OMX_ErrorUnsupportedIndex:
		{
			result = "Omx.Error.UnsupportedIndex";
			return result;
		}
		case OMX_ErrorBadPortIndex:
		{
			result = "Omx.Error.BadPortIndex";
			return result;
		}
		case OMX_ErrorPortUnpopulated:
		{
			result = "Omx.Error.PortUnpopulated";
			return result;
		}
		case OMX_ErrorComponentSuspended:
		{
			result = "Omx.Error.ComponentSuspended";
			return result;
		}
		case OMX_ErrorDynamicResourcesUnavailable:
		{
			result = "Omx.Error.DynamicResourcesUnavailable";
			return result;
		}
		case OMX_ErrorMbErrorsInFrame:
		{
			result = "Omx.Error.MbErrorsInFrame";
			return result;
		}
		case OMX_ErrorFormatNotDetected:
		{
			result = "Omx.Error.FormatNotDetected";
			return result;
		}
		case OMX_ErrorContentPipeOpenFailed:
		{
			result = "Omx.Error.ContentPipeOpenFailed";
			return result;
		}
		case OMX_ErrorContentPipeCreationFailed:
		{
			result = "Omx.Error.ContentPipeCreationFailed";
			return result;
		}
		case OMX_ErrorSeperateTablesUsed:
		{
			result = "Omx.Error.SeperateTablesUsed";
			return result;
		}
		case OMX_ErrorTunnelingUnsupported:
		{
			result = "Omx.Error.TunnelingUnsupported";
			return result;
		}
		default:
		{
			result = "(unknown)";
			return result;
		}
	}
}


static gpointer _g_error_copy0 (gpointer self) {
	return self ? g_error_copy (self) : NULL;
}


static void omx_try_run (OMX_ERRORTYPE err, const char* file, const char* function, gint line, GError** error) {
	GError * _inner_error_;
	g_return_if_fail (file != NULL);
	g_return_if_fail (function != NULL);
	_inner_error_ = NULL;
	if (err != OMX_ErrorNone) {
		GError* e;
		e = g_error_new (omx_error_domain (), (gint) err, "%s (0x%x) in function %s at %s:%d", omx_error_to_string (err), err, function, file, line, NULL);
		_inner_error_ = _g_error_copy0 ((GError*) e);
		{
			g_propagate_error (error, _inner_error_);
			_g_error_free0 (e);
			return;
		}
		_g_error_free0 (e);
	}
}


void play (const char* filename, GError** error) {
	GError * _inner_error_;
	FILE* _tmp0_;
	g_return_if_fail (filename != NULL);
	_inner_error_ = NULL;
	fd = (_tmp0_ = fopen (filename, "rb"), _fclose0 (fd), _tmp0_);
	if (fd == NULL) {
		_inner_error_ = g_error_new (G_FILE_ERROR, G_FILE_ERROR_FAILED, "Error opening %s", filename);
		{
			g_propagate_error (error, _inner_error_);
			return;
		}
	}
	omx_try_run (OMX_Init (), __FILE__, __FUNCTION__, __LINE__, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		return;
	}
	get_handles (&_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		return;
	}
	handle_print_info ("audiodec", audiodec_handle, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		return;
	}
	handle_print_info ("audiosink", audiosink_handle, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		return;
	}
	change_state_to (OMX_StateIdle, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		return;
	}
	allocate_buffers (&_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		return;
	}
	wait_for_change_of_state ();
	change_state_to (OMX_StateExecuting, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		return;
	}
	wait_for_change_of_state ();
	move_buffers (&_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		return;
	}
	wait_for_eos ();
	change_state_to (OMX_StateIdle, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		return;
	}
	wait_for_change_of_state ();
	change_state_to (OMX_StateLoaded, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		return;
	}
	free_buffers (&_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		return;
	}
	wait_for_change_of_state ();
	free_handles (&_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		return;
	}
	omx_try_run (OMX_Deinit (), __FILE__, __FUNCTION__, __LINE__, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		return;
	}
}


static OMX_ERRORTYPE _audiodec_event_handler_omx_event_handler_func (OMX_HANDLETYPE component, gpointer self, OMX_EVENTTYPE event, guint32 data1, guint32 data2, void* event_data) {
	return audiodec_event_handler (component, event, data1, data2);
}


static OMX_ERRORTYPE _audiodec_empty_buffer_done_omx_empty_buffer_done_func (OMX_HANDLETYPE component, gpointer self, OMX_BUFFERHEADERTYPE* buffer) {
	return audiodec_empty_buffer_done (component, buffer);
}


static OMX_ERRORTYPE _audiodec_fill_buffer_done_omx_fill_buffer_done_func (OMX_HANDLETYPE component, gpointer self, OMX_BUFFERHEADERTYPE* buffer) {
	return audiodec_fill_buffer_done (component, buffer);
}


static OMX_ERRORTYPE _audiosink_event_handler_omx_event_handler_func (OMX_HANDLETYPE component, gpointer self, OMX_EVENTTYPE event, guint32 data1, guint32 data2, void* event_data) {
	return audiosink_event_handler (component, event, data1, data2);
}


static OMX_ERRORTYPE _audiosink_empty_buffer_done_omx_empty_buffer_done_func (OMX_HANDLETYPE component, gpointer self, OMX_BUFFERHEADERTYPE* buffer) {
	return audiosink_empty_buffer_done (component, buffer);
}


void get_handles (GError** error) {
	GError * _inner_error_;
	_inner_error_ = NULL;
	omx_try_run (OMX_GetHandle (&audiodec_handle, AUDIODEC_COMPONENT_NAME, NULL, &audiodec_callbacks), __FILE__, __FUNCTION__, __LINE__, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		return;
	}
	omx_try_run (OMX_GetHandle (&audiosink_handle, AUDIOSINK_COMPONENT_NAME, NULL, &audiosink_callbacks), __FILE__, __FUNCTION__, __LINE__, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		return;
	}
}


static const char* omx_dir_to_string (OMX_DIRTYPE self) {
	const char* result;
	switch (self) {
		case OMX_DirInput:
		{
			result = "Omx.Dir.Input";
			return result;
		}
		case OMX_DirOutput:
		{
			result = "Omx.Dir.Output";
			return result;
		}
		default:
		{
			result = "(uknnown)";
			return result;
		}
	}
}


void handle_print_info (const char* name, OMX_HANDLETYPE handle, GError** error) {
	GError * _inner_error_;
	OMX_PORT_PARAM_TYPE _tmp0_ = {0};
	OMX_PORT_PARAM_TYPE param;
	OMX_PARAM_PORTDEFINITIONTYPE _tmp1_ = {0};
	OMX_PARAM_PORTDEFINITIONTYPE port_def;
	g_return_if_fail (name != NULL);
	_inner_error_ = NULL;
	param = (memset (&_tmp0_, 0, sizeof (OMX_PORT_PARAM_TYPE)), _tmp0_);
	omx_structure_init (&param);
	omx_try_run (OMX_GetParameter (handle, (gint) OMX_IndexParamAudioInit, &param), __FILE__, __FUNCTION__, __LINE__, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		return;
	}
	port_def = (memset (&_tmp1_, 0, sizeof (OMX_PARAM_PORTDEFINITIONTYPE)), _tmp1_);
	omx_structure_init (&port_def);
	g_print ("%s (%p)\n", name, (void*) handle);
	{
		guint i;
		i = (guint) param.nStartPortNumber;
		{
			gboolean _tmp2_;
			_tmp2_ = TRUE;
			while (TRUE) {
				if (!_tmp2_) {
					i++;
				}
				_tmp2_ = FALSE;
				if (!(i < param.nPorts)) {
					break;
				}
				g_print ("\tPort %u:\n", i);
				port_def.nPortIndex = (guint32) i;
				omx_try_run (OMX_GetParameter (handle, (gint) OMX_IndexParamPortDefinition, &port_def), __FILE__, __FUNCTION__, __LINE__, &_inner_error_);
				if (_inner_error_ != NULL) {
					g_propagate_error (error, _inner_error_);
					return;
				}
				g_print ("\t\thas mime-type %s\n", port_def.format.audio.cMIMEType);
				g_print ("\t\thas direction %s\n", omx_dir_to_string (port_def.eDir));
				g_print ("\t\thas %u buffers of size %u\n", (guint) port_def.nBufferCountActual, (guint) port_def.nBufferSize);
			}
		}
	}
}


void change_state_to (OMX_STATETYPE state, GError** error) {
	GError * _inner_error_;
	_inner_error_ = NULL;
	omx_try_run (OMX_SendCommand (audiodec_handle, OMX_CommandStateSet, (gint) state, NULL), __FILE__, __FUNCTION__, __LINE__, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		return;
	}
	omx_try_run (OMX_SendCommand (audiosink_handle, OMX_CommandStateSet, (gint) state, NULL), __FILE__, __FUNCTION__, __LINE__, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		return;
	}
}


void allocate_buffers (GError** error) {
	GError * _inner_error_;
	OMX_BUFFERHEADERTYPE** _tmp0_;
	OMX_BUFFERHEADERTYPE** _tmp1_;
	OMX_BUFFERHEADERTYPE** _tmp2_;
	_inner_error_ = NULL;
	in_buffer_audiodec = (_tmp0_ = g_new0 (OMX_BUFFERHEADERTYPE*, N_BUFFERS + 1), in_buffer_audiodec = (g_free (in_buffer_audiodec), NULL), in_buffer_audiodec_length1 = N_BUFFERS, in_buffer_audiodec_size = in_buffer_audiodec_length1, _tmp0_);
	out_buffer_audiodec = (_tmp1_ = g_new0 (OMX_BUFFERHEADERTYPE*, N_BUFFERS + 1), out_buffer_audiodec = (g_free (out_buffer_audiodec), NULL), out_buffer_audiodec_length1 = N_BUFFERS, out_buffer_audiodec_size = out_buffer_audiodec_length1, _tmp1_);
	in_buffer_audiosink = (_tmp2_ = g_new0 (OMX_BUFFERHEADERTYPE*, N_BUFFERS + 1), in_buffer_audiosink = (g_free (in_buffer_audiosink), NULL), in_buffer_audiosink_length1 = N_BUFFERS, in_buffer_audiosink_size = in_buffer_audiosink_length1, _tmp2_);
	{
		gint i;
		i = 0;
		{
			gboolean _tmp3_;
			_tmp3_ = TRUE;
			while (TRUE) {
				if (!_tmp3_) {
					i++;
				}
				_tmp3_ = FALSE;
				if (!(i < N_BUFFERS)) {
					break;
				}
				omx_try_run (OMX_AllocateBuffer (audiodec_handle, &in_buffer_audiodec[i], 0, NULL, (guint) BUFFER_IN_SIZE), __FILE__, __FUNCTION__, __LINE__, &_inner_error_);
				if (_inner_error_ != NULL) {
					g_propagate_error (error, _inner_error_);
					return;
				}
				omx_try_run (OMX_AllocateBuffer (audiodec_handle, &out_buffer_audiodec[i], 1, NULL, (guint) BUFFER_OUT_SIZE), __FILE__, __FUNCTION__, __LINE__, &_inner_error_);
				if (_inner_error_ != NULL) {
					g_propagate_error (error, _inner_error_);
					return;
				}
				omx_try_run (OMX_UseBuffer (audiosink_handle, &in_buffer_audiosink[i], 0, NULL, (guint) BUFFER_OUT_SIZE, NULL), __FILE__, __FUNCTION__, __LINE__, &_inner_error_);
				if (_inner_error_ != NULL) {
					g_propagate_error (error, _inner_error_);
					return;
				}
			}
		}
	}
}


void read_buffer_from_fd (OMX_BUFFERHEADERTYPE* buffer) {
	g_return_if_fail (buffer != NULL);
	buffer->nOffset = (gsize) 0;
	buffer->nFilledLen = fread (buffer->pBuffer, 1, buffer->nAllocLen, fd);
}


void move_buffers (GError** error) {
	GError * _inner_error_;
	_inner_error_ = NULL;
	read_buffer_from_fd (in_buffer_audiodec[0]);
	omx_try_run (OMX_EmptyThisBuffer (audiodec_handle, in_buffer_audiodec[0]), __FILE__, __FUNCTION__, __LINE__, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		return;
	}
	omx_try_run (OMX_FillThisBuffer (audiodec_handle, out_buffer_audiodec[0]), __FILE__, __FUNCTION__, __LINE__, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		return;
	}
}


void free_buffers (GError** error) {
	GError * _inner_error_;
	_inner_error_ = NULL;
	{
		gint i;
		i = 0;
		{
			gboolean _tmp0_;
			_tmp0_ = TRUE;
			while (TRUE) {
				if (!_tmp0_) {
					i++;
				}
				_tmp0_ = FALSE;
				if (!(i < N_BUFFERS)) {
					break;
				}
				omx_try_run (OMX_FreeBuffer (audiodec_handle, 0, in_buffer_audiodec[i]), __FILE__, __FUNCTION__, __LINE__, &_inner_error_);
				if (_inner_error_ != NULL) {
					g_propagate_error (error, _inner_error_);
					return;
				}
				omx_try_run (OMX_FreeBuffer (audiodec_handle, 1, out_buffer_audiodec[i]), __FILE__, __FUNCTION__, __LINE__, &_inner_error_);
				if (_inner_error_ != NULL) {
					g_propagate_error (error, _inner_error_);
					return;
				}
				omx_try_run (OMX_FreeBuffer (audiosink_handle, 0, in_buffer_audiosink[i]), __FILE__, __FUNCTION__, __LINE__, &_inner_error_);
				if (_inner_error_ != NULL) {
					g_propagate_error (error, _inner_error_);
					return;
				}
			}
		}
	}
}


void free_handles (GError** error) {
	GError * _inner_error_;
	_inner_error_ = NULL;
	omx_try_run (OMX_FreeHandle (audiodec_handle), __FILE__, __FUNCTION__, __LINE__, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		return;
	}
	omx_try_run (OMX_FreeHandle (audiosink_handle), __FILE__, __FUNCTION__, __LINE__, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		return;
	}
}


void wait_for_change_of_state (void) {
	tsem_down (&audiodec_sem);
	tsem_down (&audiosink_sem);
}


void wait_for_eos (void) {
	g_print ("Waiting for eos\n");
	tsem_down (&eos_sem);
}


OMX_ERRORTYPE audiodec_event_handler (OMX_HANDLETYPE component, OMX_EVENTTYPE event, guint32 data1, guint32 data2) {
	OMX_ERRORTYPE result;
	switch (event) {
		case OMX_EventCmdComplete:
		{
			switch (data1) {
				case OMX_CommandStateSet:
				{
					tsem_up (&audiodec_sem);
					break;
				}
				default:
				{
					break;
				}
			}
			break;
		}
		default:
		{
			break;
		}
	}
	result = OMX_ErrorNone;
	return result;
}


OMX_ERRORTYPE audiodec_empty_buffer_done (OMX_HANDLETYPE component, OMX_BUFFERHEADERTYPE* buffer) {
	OMX_ERRORTYPE result;
	g_return_val_if_fail (buffer != NULL, 0);
	if (feof (fd)) {
		result = OMX_ErrorNone;
		return result;
	}
	read_buffer_from_fd (buffer);
	if (feof (fd)) {
		g_print ("Setting eos flag\n");
		buffer->nFlags = buffer->nFlags | ((guint32) OMX_BUFFERFLAG_EOS);
	}
	result = OMX_EmptyThisBuffer (audiodec_handle, buffer);
	return result;
}


OMX_ERRORTYPE audiodec_fill_buffer_done (OMX_HANDLETYPE component, OMX_BUFFERHEADERTYPE* buffer) {
	OMX_ERRORTYPE result;
	g_return_val_if_fail (buffer != NULL, 0);
	if ((buffer->nFlags & OMX_BUFFERFLAG_EOS) != 0) {
		g_print ("Got eos flag\n");
		tsem_up (&eos_sem);
		result = OMX_ErrorNone;
		return result;
	}
	result = OMX_EmptyThisBuffer (audiosink_handle, buffer);
	return result;
}


OMX_ERRORTYPE audiosink_event_handler (OMX_HANDLETYPE component, OMX_EVENTTYPE event, guint32 data1, guint32 data2) {
	OMX_ERRORTYPE result;
	switch (event) {
		case OMX_EventCmdComplete:
		{
			switch (data1) {
				case OMX_CommandStateSet:
				{
					tsem_up (&audiosink_sem);
					break;
				}
				default:
				{
					break;
				}
			}
			break;
		}
		default:
		{
			break;
		}
	}
	result = OMX_ErrorNone;
	return result;
}


OMX_ERRORTYPE audiosink_empty_buffer_done (OMX_HANDLETYPE component, OMX_BUFFERHEADERTYPE* buffer) {
	OMX_ERRORTYPE result;
	g_return_val_if_fail (buffer != NULL, 0);
	result = OMX_FillThisBuffer (audiodec_handle, buffer);
	return result;
}




