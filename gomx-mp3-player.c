/* gomx-mp3-player.c generated by valac, the Vala compiler
 * generated from gomx-mp3-player.vala, do not modify */


#include <glib.h>
#include <glib-object.h>
#include <stdlib.h>
#include <string.h>
#include <gomx.h>
#include <stdio.h>
#include <OMX_Core.h>
#include <OMX_Component.h>

#define _g_error_free0(var) ((var == NULL) ? NULL : (var = (g_error_free (var), NULL)))
#define _fclose0(var) ((var == NULL) ? NULL : (var = (fclose (var), NULL)))
#define _g_object_unref0(var) ((var == NULL) ? NULL : (var = (g_object_unref (var), NULL)))



void play (const char* filename, GError** error);
gint _main (char** args, int args_length1);
#define AUDIODEC_ID 0
#define AUDIOSINK_ID 1



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
			if (_inner_error_->domain == G_OMX_ERROR) {
				goto __catch0_g_omx_error;
			}
			goto __catch0_g_error;
		}
		result = 0;
		return result;
	}
	goto __finally0;
	__catch0_g_omx_error:
	{
		GError * e;
		e = _inner_error_;
		_inner_error_ = NULL;
		{
			g_print ("An error of omx occurred\n");
			g_print ("%s\n", e->message);
			result = 1;
			_g_error_free0 (e);
			return result;
		}
	}
	goto __finally0;
	__catch0_g_error:
	{
		GError * e;
		e = _inner_error_;
		_inner_error_ = NULL;
		{
			g_print ("An error of glib occurred\n");
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
	g_thread_init (NULL);
	g_type_init ();
	return _main (argv, argc);
}


void play (const char* filename, GError** error) {
	GError * _inner_error_;
	FILE* fd;
	GOmxCore* core;
	GOmxAudioComponent* audiodec;
	GOmxAudioComponent* audiosink;
	GOmxEngine* engine;
	g_return_if_fail (filename != NULL);
	_inner_error_ = NULL;
	fd = fopen (filename, "rb");
	if (fd == NULL) {
		_inner_error_ = g_error_new (G_FILE_ERROR, G_FILE_ERROR_FAILED, "Error opening %s", filename);
		{
			g_propagate_error (error, _inner_error_);
			_fclose0 (fd);
			return;
		}
	}
	core = g_omx_core_open ("libomxil-bellagio.so.0");
	g_omx_core_init (core, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		_fclose0 (fd);
		_g_object_unref0 (core);
		return;
	}
	audiodec = g_omx_audio_component_new (core, "OMX.st.audio_decoder.mp3.mad");
	g_omx_component_set_name ((GOmxComponent*) audiodec, "audiodec");
	audiosink = g_omx_audio_component_new (core, "OMX.st.alsa.alsasink");
	g_omx_component_set_name ((GOmxComponent*) audiosink, "audiosink");
	engine = g_omx_engine_new ();
	g_omx_engine_add_component (engine, (guint) AUDIODEC_ID, (GOmxComponent*) audiodec);
	g_omx_engine_add_component (engine, (guint) AUDIOSINK_ID, (GOmxComponent*) audiosink);
	g_omx_component_list_init (g_omx_engine_get_components (engine), &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		_fclose0 (fd);
		_g_object_unref0 (core);
		_g_object_unref0 (audiodec);
		_g_object_unref0 (audiosink);
		_g_object_unref0 (engine);
		return;
	}
	g_omx_component_list_set_state_and_wait (g_omx_engine_get_components (engine), OMX_StateIdle, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		_fclose0 (fd);
		_g_object_unref0 (core);
		_g_object_unref0 (audiodec);
		_g_object_unref0 (audiosink);
		_g_object_unref0 (engine);
		return;
	}
	g_omx_component_list_set_state_and_wait (g_omx_engine_get_components (engine), OMX_StateExecuting, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		_fclose0 (fd);
		_g_object_unref0 (core);
		_g_object_unref0 (audiodec);
		_g_object_unref0 (audiosink);
		_g_object_unref0 (engine);
		return;
	}
	g_omx_engine_buffers_begin_transfer (engine, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		_fclose0 (fd);
		_g_object_unref0 (core);
		_g_object_unref0 (audiodec);
		_g_object_unref0 (audiosink);
		_g_object_unref0 (engine);
		return;
	}
	{
		GOmxPortDoneQueueIterator* _port_it;
		_port_it = g_omx_port_done_queue_iterator (g_omx_engine_get_ports_with_buffer_done (engine));
		while (TRUE) {
			GOmxPort* port;
			if (!g_omx_port_done_queue_iterator_next (_port_it)) {
				break;
			}
			port = g_omx_port_done_queue_iterator_get (_port_it);
			switch (g_omx_port_get_component (port)->id) {
				case AUDIODEC_ID:
				{
					switch (port->definition.eDir) {
						case OMX_DirInput:
						{
							{
								OMX_BUFFERHEADERTYPE* buffer;
								buffer = g_omx_port_pop_buffer (port);
								g_omx_buffer_read_from_file (buffer, fd);
								g_omx_port_push_buffer (port, buffer, &_inner_error_);
								if (_inner_error_ != NULL) {
									g_propagate_error (error, _inner_error_);
									_g_object_unref0 (port);
									_g_object_unref0 (_port_it);
									_fclose0 (fd);
									_g_object_unref0 (core);
									_g_object_unref0 (audiodec);
									_g_object_unref0 (audiosink);
									_g_object_unref0 (engine);
									return;
								}
								break;
							}
						}
						case OMX_DirOutput:
						{
							{
								OMX_BUFFERHEADERTYPE* buffer;
								GOmxPort* audiosink_inport;
								OMX_BUFFERHEADERTYPE* audiosink_buffer;
								buffer = g_omx_port_pop_buffer (port);
								audiosink_inport = g_omx_port_array_get (g_omx_component_get_ports ((GOmxComponent*) audiosink), (guint) 0);
								audiosink_buffer = g_omx_port_pop_buffer (audiosink_inport);
								g_omx_buffer_copy (audiosink_buffer, buffer);
								g_omx_port_push_buffer (audiosink_inport, audiosink_buffer, &_inner_error_);
								if (_inner_error_ != NULL) {
									g_propagate_error (error, _inner_error_);
									_g_object_unref0 (audiosink_inport);
									_g_object_unref0 (port);
									_g_object_unref0 (_port_it);
									_fclose0 (fd);
									_g_object_unref0 (core);
									_g_object_unref0 (audiodec);
									_g_object_unref0 (audiosink);
									_g_object_unref0 (engine);
									return;
								}
								g_omx_port_push_buffer (port, buffer, &_inner_error_);
								if (_inner_error_ != NULL) {
									g_propagate_error (error, _inner_error_);
									_g_object_unref0 (audiosink_inport);
									_g_object_unref0 (port);
									_g_object_unref0 (_port_it);
									_fclose0 (fd);
									_g_object_unref0 (core);
									_g_object_unref0 (audiodec);
									_g_object_unref0 (audiosink);
									_g_object_unref0 (engine);
									return;
								}
								_g_object_unref0 (audiosink_inport);
								break;
							}
						}
						default:
						{
							break;
						}
					}
					break;
				}
				case AUDIOSINK_ID:
				{
					switch (port->definition.eDir) {
						case OMX_DirInput:
						{
							break;
						}
						default:
						{
							break;
						}
					}
					break;
				}
			}
			_g_object_unref0 (port);
		}
		_g_object_unref0 (_port_it);
	}
	g_omx_component_list_set_state_and_wait (g_omx_engine_get_components (engine), OMX_StateIdle, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		_fclose0 (fd);
		_g_object_unref0 (core);
		_g_object_unref0 (audiodec);
		_g_object_unref0 (audiosink);
		_g_object_unref0 (engine);
		return;
	}
	g_omx_component_list_set_state_and_wait (g_omx_engine_get_components (engine), OMX_StateLoaded, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		_fclose0 (fd);
		_g_object_unref0 (core);
		_g_object_unref0 (audiodec);
		_g_object_unref0 (audiosink);
		_g_object_unref0 (engine);
		return;
	}
	g_omx_component_list_free_handles (g_omx_engine_get_components (engine), &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		_fclose0 (fd);
		_g_object_unref0 (core);
		_g_object_unref0 (audiodec);
		_g_object_unref0 (audiosink);
		_g_object_unref0 (engine);
		return;
	}
	g_omx_core_deinit (core, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		_fclose0 (fd);
		_g_object_unref0 (core);
		_g_object_unref0 (audiodec);
		_g_object_unref0 (audiosink);
		_g_object_unref0 (engine);
		return;
	}
	_fclose0 (fd);
	_g_object_unref0 (core);
	_g_object_unref0 (audiodec);
	_g_object_unref0 (audiosink);
	_g_object_unref0 (engine);
}




