/* simple-mp3-player.c generated by valac, the Vala compiler
 * generated from simple-mp3-player.vala, do not modify */


#include <glib.h>
#include <glib-object.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <OMX_Core.h>
#include <OMX_Component.h>
#include <omx-utils.h>
#include <bellagio/tsemaphore.h>

#define _g_error_free0(var) ((var == NULL) ? NULL : (var = (g_error_free (var), NULL)))
#define _fclose0(var) ((var == NULL) ? NULL : (var = (fclose (var), NULL)))


extern FILE* fd;
FILE* fd = NULL;
extern void* audiodec_handle;
extern void* audiosink_handle;
void* audiodec_handle = NULL;
void* audiosink_handle = NULL;
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
void handle_print_info (const char* name, void* handle, GError** error);
void set_state (OMX_STATETYPE state, GError** error);
void allocate_buffers (GError** error);
void wait_for_state_set (void);
void move_buffers (GError** error);
void wait_for_eos (void);
void free_buffers (GError** error);
void free_handles (GError** error);
OMX_ERRORTYPE audiodec_event_handler (void* component, OMX_EVENTTYPE event, guint32 data1, guint32 data2);
static OMX_ERRORTYPE _audiodec_event_handler_omx_event_handler_func (void* component, gpointer self, OMX_EVENTTYPE event, guint32 data1, guint32 data2, void* event_data);
OMX_ERRORTYPE audiodec_empty_buffer_done (void* component, OMX_BUFFERHEADERTYPE* buffer);
static OMX_ERRORTYPE _audiodec_empty_buffer_done_omx_empty_buffer_done_func (void* component, gpointer self, OMX_BUFFERHEADERTYPE* buffer);
OMX_ERRORTYPE audiodec_fill_buffer_done (void* component, OMX_BUFFERHEADERTYPE* buffer);
static OMX_ERRORTYPE _audiodec_fill_buffer_done_omx_fill_buffer_done_func (void* component, gpointer self, OMX_BUFFERHEADERTYPE* buffer);
OMX_ERRORTYPE audiosink_event_handler (void* component, OMX_EVENTTYPE event, guint32 data1, guint32 data2);
static OMX_ERRORTYPE _audiosink_event_handler_omx_event_handler_func (void* component, gpointer self, OMX_EVENTTYPE event, guint32 data1, guint32 data2, void* event_data);
OMX_ERRORTYPE audiosink_empty_buffer_done (void* component, OMX_BUFFERHEADERTYPE* buffer);
static OMX_ERRORTYPE _audiosink_empty_buffer_done_omx_empty_buffer_done_func (void* component, gpointer self, OMX_BUFFERHEADERTYPE* buffer);
#define AUDIODEC_COMPONENT "OMX.st.audio_decoder.mp3.mad"
#define AUDIOSINK_COMPONENT "OMX.st.alsa.alsasink"
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
			result = "The function returned successfully";
			return result;
		}
		case OMX_ErrorInsufficientResources:
		{
			result = "There were insufficient resources to perform the requested operation";
			return result;
		}
		case OMX_ErrorUndefined:
		{
			result = "There was an error but the cause of the error could not be determined";
			return result;
		}
		case OMX_ErrorInvalidComponentName:
		{
			result = "The component name string was invalid";
			return result;
		}
		case OMX_ErrorComponentNotFound:
		{
			result = "No component with the specified name string was found";
			return result;
		}
		case OMX_ErrorInvalidComponent:
		{
			result = "The component name string was invalid";
			return result;
		}
		case OMX_ErrorBadParameter:
		{
			result = "One or more parameters were invalid";
			return result;
		}
		case OMX_ErrorNotImplemented:
		{
			result = "The requested function is not implemented";
			return result;
		}
		case OMX_ErrorUnderflow:
		{
			result = "The buffer was emptied before the next buffer was ready";
			return result;
		}
		case OMX_ErrorOverflow:
		{
			result = "The buffer was not available when it was needed";
			return result;
		}
		case OMX_ErrorHardware:
		{
			result = "The hardware failed to respond as expected";
			return result;
		}
		case OMX_ErrorInvalidState:
		{
			result = "The component is in the OMX_StateInvalid state";
			return result;
		}
		case OMX_ErrorStreamCorrupt:
		{
			result = "The stream is found to be corrupt";
			return result;
		}
		case OMX_ErrorPortsNotCompatible:
		{
			result = "Ports being set up for tunneled communication are incompatible";
			return result;
		}
		case OMX_ErrorResourcesLost:
		{
			result = "Resources allocated to a component in the OMX_StateIdle state have been lost";
			return result;
		}
		case OMX_ErrorNoMore:
		{
			result = "No more indices can be enumerated";
			return result;
		}
		case OMX_ErrorVersionMismatch:
		{
			result = "The component detected a version mismatch";
			return result;
		}
		case OMX_ErrorNotReady:
		{
			result = "The component is not ready to return data at this time";
			return result;
		}
		case OMX_ErrorTimeout:
		{
			result = "A timeout occurred where the component was unable to process the call in a reasonable amount of time";
			return result;
		}
		case OMX_ErrorSameState:
		{
			result = "The component tried to transition into the state that it is currently in";
			return result;
		}
		case OMX_ErrorResourcesPreempted:
		{
			result = "Resources allocated to a component in the OMX_StateExecuting or OMX_StatePause states have been pre-empted";
			return result;
		}
		case OMX_ErrorPortUnresponsiveDuringAllocation:
		{
			result = "The non-supplier port deemed that it had waited an unusually long time for the supplier port to send it an allocated buffer via an OMX_UseBuffer call";
			return result;
		}
		case OMX_ErrorPortUnresponsiveDuringDeallocation:
		{
			result = "The non-supplier port deemed that it had waited an unusually long time for the supplier port to request the de-allocation of a buffer header via a OMX_FreeBuffer call";
			return result;
		}
		case OMX_ErrorPortUnresponsiveDuringStop:
		{
			result = "The supplier port deemed that it had waited an unusually long time for the non-supplier port to return a buffer via an EmptyThisBuffer or FillThisBuffer call";
			return result;
		}
		case OMX_ErrorIncorrectStateTransition:
		{
			result = "A state transition was attempted that is not allowed.";
			return result;
		}
		case OMX_ErrorIncorrectStateOperation:
		{
			result = "A command or method was attempted that is not allowed during the present state";
			return result;
		}
		case OMX_ErrorUnsupportedSetting:
		{
			result = "One or more values encapsulated in the parameter or configuration structure are unsupported";
			return result;
		}
		case OMX_ErrorUnsupportedIndex:
		{
			result = "The parameter or configuration indicated by the given index is unsupported";
			return result;
		}
		case OMX_ErrorBadPortIndex:
		{
			result = "The port index that was supplied is incorrect";
			return result;
		}
		case OMX_ErrorPortUnpopulated:
		{
			result = "The port has lost one or more of its buffers and is thus unpopulated";
			return result;
		}
		case OMX_ErrorComponentSuspended:
		{
			result = "Component suspended due to temporary loss of resources";
			return result;
		}
		case OMX_ErrorDynamicResourcesUnavailable:
		{
			result = "Component suspended due to inability to acquire dynamic resources";
			return result;
		}
		case OMX_ErrorMbErrorsInFrame:
		{
			result = "Errors detected in frame";
			return result;
		}
		case OMX_ErrorFormatNotDetected:
		{
			result = "Component cannot parse or determine the format of the given datastream";
			return result;
		}
		case OMX_ErrorContentPipeOpenFailed:
		{
			result = "Opening the Content Pipe failed";
			return result;
		}
		case OMX_ErrorContentPipeCreationFailed:
		{
			result = "Creating the Content Pipe failed";
			return result;
		}
		case OMX_ErrorSeperateTablesUsed:
		{
			result = "Attempting to query for single Chroma table when separate quantization tables are used for the Chroma (Cb and Cr) coefficients";
			return result;
		}
		case OMX_ErrorTunnelingUnsupported:
		{
			result = "Tunneling is not supported by the component";
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
		_inner_error_ = _g_error_copy0 (e);
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
	set_state (OMX_StateIdle, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		return;
	}
	allocate_buffers (&_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		return;
	}
	wait_for_state_set ();
	set_state (OMX_StateExecuting, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		return;
	}
	wait_for_state_set ();
	move_buffers (&_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		return;
	}
	wait_for_eos ();
	set_state (OMX_StateIdle, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		return;
	}
	wait_for_state_set ();
	set_state (OMX_StateLoaded, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		return;
	}
	free_buffers (&_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		return;
	}
	wait_for_state_set ();
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


static OMX_ERRORTYPE _audiodec_event_handler_omx_event_handler_func (void* component, gpointer self, OMX_EVENTTYPE event, guint32 data1, guint32 data2, void* event_data) {
	return audiodec_event_handler (component, event, data1, data2);
}


static OMX_ERRORTYPE _audiodec_empty_buffer_done_omx_empty_buffer_done_func (void* component, gpointer self, OMX_BUFFERHEADERTYPE* buffer) {
	return audiodec_empty_buffer_done (component, buffer);
}


static OMX_ERRORTYPE _audiodec_fill_buffer_done_omx_fill_buffer_done_func (void* component, gpointer self, OMX_BUFFERHEADERTYPE* buffer) {
	return audiodec_fill_buffer_done (component, buffer);
}


static OMX_ERRORTYPE _audiosink_event_handler_omx_event_handler_func (void* component, gpointer self, OMX_EVENTTYPE event, guint32 data1, guint32 data2, void* event_data) {
	return audiosink_event_handler (component, event, data1, data2);
}


static OMX_ERRORTYPE _audiosink_empty_buffer_done_omx_empty_buffer_done_func (void* component, gpointer self, OMX_BUFFERHEADERTYPE* buffer) {
	return audiosink_empty_buffer_done (component, buffer);
}


void get_handles (GError** error) {
	GError * _inner_error_;
	_inner_error_ = NULL;
	omx_try_run (OMX_GetHandle (&audiodec_handle, AUDIODEC_COMPONENT, NULL, &audiodec_callbacks), __FILE__, __FUNCTION__, __LINE__, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		return;
	}
	omx_try_run (OMX_GetHandle (&audiosink_handle, AUDIOSINK_COMPONENT, NULL, &audiosink_callbacks), __FILE__, __FUNCTION__, __LINE__, &_inner_error_);
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


void handle_print_info (const char* name, void* handle, GError** error) {
	GError * _inner_error_;
	OMX_PORT_PARAM_TYPE _tmp0_ = {0};
	OMX_PORT_PARAM_TYPE param;
	OMX_PARAM_PORTDEFINITIONTYPE _tmp1_ = {0};
	OMX_PARAM_PORTDEFINITIONTYPE port_definition;
	g_return_if_fail (name != NULL);
	g_return_if_fail (handle != NULL);
	_inner_error_ = NULL;
	param = (memset (&_tmp0_, 0, sizeof (OMX_PORT_PARAM_TYPE)), _tmp0_);
	omx_structure_init (&param);
	omx_try_run (OMX_GetParameter (handle, (guint) OMX_IndexParamAudioInit, &param), __FILE__, __FUNCTION__, __LINE__, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		return;
	}
	port_definition = (memset (&_tmp1_, 0, sizeof (OMX_PARAM_PORTDEFINITIONTYPE)), _tmp1_);
	omx_structure_init (&port_definition);
	g_print ("%s (%p)\n", name, handle);
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
				port_definition.nPortIndex = (guint32) i;
				omx_try_run (OMX_GetParameter (handle, (guint) OMX_IndexParamPortDefinition, &port_definition), __FILE__, __FUNCTION__, __LINE__, &_inner_error_);
				if (_inner_error_ != NULL) {
					g_propagate_error (error, _inner_error_);
					return;
				}
				g_print ("\t\thas mime-type %s\n", port_definition.format.audio.cMIMEType);
				g_print ("\t\thas direction %s\n", omx_dir_to_string (port_definition.eDir));
				g_print ("\t\thas %u buffers of size %u\n", (guint) port_definition.nBufferCountActual, (guint) port_definition.nBufferSize);
			}
		}
	}
}


void set_state (OMX_STATETYPE state, GError** error) {
	GError * _inner_error_;
	_inner_error_ = NULL;
	omx_try_run (OMX_SendCommand (audiodec_handle, OMX_CommandStateSet, (guint) state, NULL), __FILE__, __FUNCTION__, __LINE__, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		return;
	}
	omx_try_run (OMX_SendCommand (audiosink_handle, OMX_CommandStateSet, (guint) state, NULL), __FILE__, __FUNCTION__, __LINE__, &_inner_error_);
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
				omx_try_run (OMX_AllocateBuffer (audiodec_handle, &in_buffer_audiodec[i], (guint) 0, NULL, (guint) BUFFER_IN_SIZE), __FILE__, __FUNCTION__, __LINE__, &_inner_error_);
				if (_inner_error_ != NULL) {
					g_propagate_error (error, _inner_error_);
					return;
				}
				omx_try_run (OMX_AllocateBuffer (audiodec_handle, &out_buffer_audiodec[i], (guint) 1, NULL, (guint) BUFFER_OUT_SIZE), __FILE__, __FUNCTION__, __LINE__, &_inner_error_);
				if (_inner_error_ != NULL) {
					g_propagate_error (error, _inner_error_);
					return;
				}
				omx_try_run (OMX_AllocateBuffer (audiosink_handle, &in_buffer_audiosink[i], (guint) 0, NULL, (guint) BUFFER_OUT_SIZE), __FILE__, __FUNCTION__, __LINE__, &_inner_error_);
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
				read_buffer_from_fd (in_buffer_audiodec[i]);
				omx_try_run (OMX_EmptyThisBuffer (audiodec_handle, in_buffer_audiodec[i]), __FILE__, __FUNCTION__, __LINE__, &_inner_error_);
				if (_inner_error_ != NULL) {
					g_propagate_error (error, _inner_error_);
					return;
				}
				omx_try_run (OMX_FillThisBuffer (audiodec_handle, out_buffer_audiodec[i]), __FILE__, __FUNCTION__, __LINE__, &_inner_error_);
				if (_inner_error_ != NULL) {
					g_propagate_error (error, _inner_error_);
					return;
				}
			}
		}
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
				omx_try_run (OMX_FreeBuffer (audiodec_handle, (guint) 0, in_buffer_audiodec[i]), __FILE__, __FUNCTION__, __LINE__, &_inner_error_);
				if (_inner_error_ != NULL) {
					g_propagate_error (error, _inner_error_);
					return;
				}
				omx_try_run (OMX_FreeBuffer (audiodec_handle, (guint) 1, out_buffer_audiodec[i]), __FILE__, __FUNCTION__, __LINE__, &_inner_error_);
				if (_inner_error_ != NULL) {
					g_propagate_error (error, _inner_error_);
					return;
				}
				omx_try_run (OMX_FreeBuffer (audiosink_handle, (guint) 0, in_buffer_audiosink[i]), __FILE__, __FUNCTION__, __LINE__, &_inner_error_);
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


void wait_for_state_set (void) {
	tsem_down (&audiodec_sem);
	tsem_down (&audiosink_sem);
}


void wait_for_eos (void) {
	g_print ("Waiting for eos\n");
	tsem_down (&eos_sem);
}


OMX_ERRORTYPE audiodec_event_handler (void* component, OMX_EVENTTYPE event, guint32 data1, guint32 data2) {
	OMX_ERRORTYPE result;
	g_return_val_if_fail (component != NULL, 0);
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


static void omx_buffer_header_set_eos (OMX_BUFFERHEADERTYPE* self) {
	g_return_if_fail (self != NULL);
	self->nFlags = self->nFlags | ((guint32) OMX_BUFFERFLAG_EOS);
}


OMX_ERRORTYPE audiodec_empty_buffer_done (void* component, OMX_BUFFERHEADERTYPE* buffer) {
	OMX_ERRORTYPE result;
	g_return_val_if_fail (component != NULL, 0);
	g_return_val_if_fail (buffer != NULL, 0);
	if (feof (fd)) {
		result = OMX_ErrorNone;
		return result;
	}
	read_buffer_from_fd (buffer);
	if (feof (fd)) {
		g_print ("Setting eos flag\n");
		omx_buffer_header_set_eos (buffer);
	}
	result = OMX_EmptyThisBuffer (audiodec_handle, buffer);
	return result;
}


static gboolean omx_buffer_header_get_eos (OMX_BUFFERHEADERTYPE* self) {
	gboolean result;
	g_return_val_if_fail (self != NULL, FALSE);
	result = (self->nFlags & OMX_BUFFERFLAG_EOS) != 0;
	return result;
}


OMX_ERRORTYPE audiodec_fill_buffer_done (void* component, OMX_BUFFERHEADERTYPE* buffer) {
	OMX_ERRORTYPE result;
	g_return_val_if_fail (component != NULL, 0);
	g_return_val_if_fail (buffer != NULL, 0);
	if (omx_buffer_header_get_eos (buffer)) {
		g_print ("Got eos flag\n");
		tsem_up (&eos_sem);
		result = OMX_ErrorNone;
		return result;
	}
	result = OMX_EmptyThisBuffer (audiosink_handle, buffer);
	return result;
}


OMX_ERRORTYPE audiosink_event_handler (void* component, OMX_EVENTTYPE event, guint32 data1, guint32 data2) {
	OMX_ERRORTYPE result;
	g_return_val_if_fail (component != NULL, 0);
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


OMX_ERRORTYPE audiosink_empty_buffer_done (void* component, OMX_BUFFERHEADERTYPE* buffer) {
	OMX_ERRORTYPE result;
	g_return_val_if_fail (component != NULL, 0);
	g_return_val_if_fail (buffer != NULL, 0);
	result = OMX_FillThisBuffer (audiodec_handle, buffer);
	return result;
}




