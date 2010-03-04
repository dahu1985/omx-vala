/* gomx.vapi generated by valac, do not modify. */

[CCode (cprefix = "GOmx", lower_case_cprefix = "g_omx_")]
namespace GOmx {
	[CCode (cheader_filename = "gomx.h")]
	public class AudioComponent : GOmx.Component {
		public AudioComponent (GOmx.Core core, string name);
	}
	[CCode (cheader_filename = "gomx.h")]
	public class Component : GLib.Object {
		[CCode (cheader_filename = "gomx.h", instance_pos = -2)]
		public delegate void EventFunc (GOmx.Component component, uint data1, uint data2, void* event_data);
		public uint id;
		public Omx.PortParam ports_param;
		public Component (GOmx.Core core, string name, Omx.Index index);
		protected virtual void allocate_ports () throws GOmx.Error;
		public virtual void buffers_begin_transfer () throws GOmx.Error;
		public Omx.Error can_set_state (Omx.State next_state);
		public void event_set_function (Omx.Event event, GOmx.Component.EventFunc event_function);
		public virtual void free_handle () throws GOmx.Error;
		protected virtual void free_ports () throws GOmx.Error;
		public uint get_n_ports ();
		public Omx.State get_state () throws GOmx.Error;
		public virtual void init () throws GOmx.Error;
		public virtual void set_role ();
		public virtual void set_state (Omx.State state) throws GOmx.Error;
		public void set_state_and_wait (Omx.State state) throws GOmx.Error;
		public virtual void wait_for_flush ();
		public virtual void wait_for_port () throws GOmx.Error;
		public virtual void wait_for_state ();
		public string component_name { get; set construct; }
		public string? component_role { get; set construct; }
		public GOmx.Core core { get; set construct; }
		public uint current_state { get; }
		public Omx.Handle handle { get; }
		public uint init_index { get; set construct; }
		public string name { get; set; }
		public bool no_allocate_buffers { get; set; }
		public uint pending_state { get; }
		public GOmx.PortArray ports { get; }
		public uint previous_state { get; }
		public GLib.AsyncQueue<GOmx.Port>? queue { get; set; }
	}
	[CCode (cheader_filename = "gomx.h")]
	public class ComponentList : GLib.Object {
		[CCode (cheader_filename = "gomx.h")]
		public class Iterator : GLib.Object {
			public Iterator (GOmx.ComponentList list);
			public GOmx.Component @get ();
			public bool next ();
		}
		public ComponentList ();
		public void add (GOmx.Component component);
		public void free_handles () throws GOmx.Error;
		public GOmx.Component @get (uint index);
		public void init () throws GOmx.Error;
		public GOmx.ComponentList.Iterator iterator ();
		public virtual void set_state (Omx.State state) throws GOmx.Error;
		public void set_state_and_wait (Omx.State state) throws GOmx.Error;
		public void wait_for_state_set ();
		public uint length { get; }
	}
	[CCode (cheader_filename = "gomx.h")]
	public class Core : GLib.Object {
		[CCode (cheader_filename = "gomx.h", instance_pos = -2)]
		public delegate Omx.Error DeinitFunc ();
		[CCode (cheader_filename = "gomx.h", instance_pos = -2)]
		public delegate Omx.Error FreeHandleFunc (Omx.Handle handle);
		[CCode (cheader_filename = "gomx.h", instance_pos = -2)]
		public delegate Omx.Error GetHandleFunc (out Omx.Handle component, string component_name, void* app_data, Omx.Callback callbacks);
		[CCode (cheader_filename = "gomx.h", instance_pos = -2)]
		public delegate Omx.Error InitFunc ();
		[CCode (cheader_filename = "gomx.h", instance_pos = -2)]
		public delegate Omx.Error SetupTunnelFunc (Omx.Handle output, uint32 port_output, Omx.Handle input, uint32 port_input);
		public Core ();
		public void deinit () throws GOmx.Error;
		public void free_handle (Omx.Handle handle) throws GOmx.Error;
		public void get_handle (out Omx.Handle component, string component_name, void* app_data, Omx.Callback callbacks) throws GOmx.Error;
		public void init () throws GOmx.Error;
		public static GOmx.Core? open (string soname);
		public void setup_tunnel (Omx.Handle output, uint32 port_output, Omx.Handle input, uint32 port_input) throws GOmx.Error;
		public GLib.Module module { get; }
	}
	[CCode (cheader_filename = "gomx.h")]
	public class Engine : GLib.Object {
		public Engine ();
		public virtual void add_component (uint id, GOmx.Component component);
		public virtual void buffers_begin_transfer () throws GOmx.Error;
		public GOmx.ComponentList components { get; }
		public GOmx.PortDoneQueue ports_with_buffer_done { get; }
	}
	[CCode (cheader_filename = "gomx.h")]
	public class ImageComponent : GOmx.Component {
		public ImageComponent (GOmx.Core core, string name);
	}
	[CCode (cheader_filename = "gomx.h")]
	public class OtherComponent : GOmx.Component {
		public OtherComponent (GOmx.Core core, string name);
	}
	[CCode (cheader_filename = "gomx.h")]
	public class Port : GLib.Object {
		[CCode (cheader_filename = "gomx.h", instance_pos = -2)]
		public delegate void BufferDoneFunc (Omx.BufferHeader buffer);
		public Omx.Param.PortDefinition definition;
		public Port (GOmx.Component component, uint32 index);
		public void allocate_buffers () throws GOmx.Error;
		public void buffer_done (Omx.BufferHeader buffer);
		public void buffers_begin_transfer () throws GOmx.Error;
		public void disable () throws GOmx.Error;
		public void enable () throws GOmx.Error;
		public void flush () throws GOmx.Error;
		public void free_buffers () throws GOmx.Error;
		public uint get_buffer_size ();
		public void get_definition () throws GOmx.Error;
		public uint get_n_buffers ();
		public void init () throws GOmx.Error;
		public Omx.BufferHeader pop_buffer ();
		public void push_buffer (Omx.BufferHeader buffer) throws GOmx.Error;
		public void set_buffer_done_function (GOmx.Port.BufferDoneFunc buffer_done_func);
		public void set_definition () throws GOmx.Error;
		public void setup_tunnel_with_port (GOmx.Port port) throws GOmx.Error;
		public void use_buffers_of_array (uint8[][] array) throws GOmx.Error;
		public void use_buffers_of_port (GOmx.Port port) throws GOmx.Error;
		public GOmx.Component component { get; set construct; }
		public bool eos { get; }
		public uint index { get; set; }
		public string name { get; set; }
		public GOmx.Port? peer { get; }
		public GLib.AsyncQueue<Omx.BufferHeader> queue { get; }
	}
	[CCode (cheader_filename = "gomx.h")]
	public class PortArray : GLib.Object {
		[CCode (cheader_filename = "gomx.h")]
		public class Iterator : GLib.Object {
			public Iterator (GOmx.PortArray array);
			public GOmx.Port @get ();
			public bool next ();
		}
		public PortArray (uint length, uint start = 0);
		public GOmx.Port @get (uint index);
		public GOmx.PortArray.Iterator iterator ();
		public void @set (uint index, GOmx.Port port);
		public uint length { get; set construct; }
		public uint start { get; set construct; }
	}
	[CCode (cheader_filename = "gomx.h")]
	public class PortDoneQueue : GLib.Object {
		[CCode (cheader_filename = "gomx.h")]
		public class Iterator : GLib.Object {
			public Iterator (GOmx.PortDoneQueue queue);
			public GOmx.Port @get ();
			public bool next ();
		}
		public PortDoneQueue ();
		public GOmx.PortDoneQueue.Iterator iterator ();
		public GLib.AsyncQueue<GOmx.Port> queue { get; }
	}
	[CCode (cheader_filename = "gomx.h")]
	public class Semaphore : GLib.Object {
		public Semaphore ();
		public void down ();
		public void up ();
	}
	[CCode (cheader_filename = "gomx.h")]
	public class VideoComponent : GOmx.Component {
		public VideoComponent (GOmx.Core core, string name);
	}
	[CCode (cprefix = "G_OMX_ERROR_", cheader_filename = "gomx.h")]
	public errordomain Error {
		None,
		InsufficientResources,
		Undefined,
		InvalidComponentName,
		ComponentNotFound,
		InvalidComponent,
		BadParameter,
		NotImplemented,
		Underflow,
		Overflow,
		Hardware,
		InvalidState,
		StreamCorrupt,
		PortsNotCompatible,
		ResourcesLost,
		NoMore,
		VersionMismatch,
		NotReady,
		Timeout,
		SameState,
		ResourcesPreempted,
		PortUnresponsiveDuringAllocation,
		PortUnresponsiveDuringDeallocation,
		PortUnresponsiveDuringStop,
		IncorrectStateTransition,
		IncorrectStateOperation,
		UnsupportedSetting,
		UnsupportedIndex,
		BadPortIndex,
		PortUnpopulated,
		ComponentSuspended,
		DynamicResourcesUnavailable,
		MbErrorsInFrame,
		FormatNotDetected,
		ContentPipeOpenFailed,
		ContentPipeCreationFailed,
		SeperateTablesUsed,
		TunnelingUnsupported,
	}
	[CCode (cheader_filename = "gomx.h")]
	public static void buffer_copy (Omx.BufferHeader dest, Omx.BufferHeader source);
	[CCode (cheader_filename = "gomx.h")]
	public static void buffer_copy_len (Omx.BufferHeader dest, Omx.BufferHeader source);
	[CCode (cheader_filename = "gomx.h")]
	public static bool buffer_is_eos (Omx.BufferHeader buffer);
	[CCode (cheader_filename = "gomx.h")]
	public static void buffer_read_from_file (Omx.BufferHeader buffer, GLib.FileStream fs);
	[CCode (cheader_filename = "gomx.h")]
	public static void buffer_set_eos (Omx.BufferHeader buffer);
	[CCode (cheader_filename = "gomx.h")]
	public static unowned string command_to_string (Omx.Command command);
	[CCode (cheader_filename = "gomx.h")]
	public static unowned string error_to_string (Omx.Error error);
	[CCode (cheader_filename = "gomx.h")]
	public static unowned string event_to_string (Omx.Event event);
	[CCode (cheader_filename = "gomx.h")]
	public static unowned string state_to_string (Omx.State state);
	[CCode (cheader_filename = "gomx.h")]
	public static void try_run (Omx.Error e) throws GOmx.Error;
}
