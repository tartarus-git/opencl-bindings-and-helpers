#pragma once

#include <cstdint>                                                                                  // Used for fixed-width types.
#include <string>																					// Used for access to std::string.

// NOTE: These almost definitely only work in Windows, so if you ever want to port this to another system, these definitely need to change.
#define CL_API_CALL _stdcall                                                                        // Calling covention for the OpenCL API calls.
#define CL_CALLBACK _stdcall																		// Calling convention for the OpenCL callback functions.

// NOTE: OpenCL is backwards-compatible. So stuff from older versions stays for newer versions unless it's been deprecated.
// NOTE: OpenCL has this CL_VERSION_X_X define system, where every define for every version under or equal to the version you're currently targeting is defined.
// NOTE: That basically reflects the backwards-compatibility. Every feature of every older version is active in the newer versions. Deprecation is handled extra.

// NOTE: The way this library will work is that it'll assume you're targeting the latest version and give you all the tools you need for that.
// NOTE: Since OpenCL is backwards-compatible though, you can target whichever version you want or decide at runtime, and as long as you don't use deprecated
// NOTE: features, you should be able to rely on it working just fine.

// NOTE: So that you know which features will be available and which won't inside the actual DLL that you're going to be linking with based on the version info that
// NOTE: it gives you, I'm going to comment which features were introduced in which version. Uncommented features have been there since the beginning and are super
// NOTE: safe to use.

#define CL_EXT_VERSION_STRING_PREFIX_LENGTH 10			// TODO: Put in actual number.

// NOTE: Floats in OpenCL are always 32-bit as far as I can tell by looking at the docs, so don't worry about other sizes.
#define CL_EXT_FLOAT_SIZE 4

/* Error Codes */
#define CL_SUCCESS									 0
#define CL_DEVICE_NOT_FOUND							-1
#define CL_DEVICE_NOT_AVAILABLE                     -2
#define CL_COMPILER_NOT_AVAILABLE                   -3
#define CL_MEM_OBJECT_ALLOCATION_FAILURE            -4
#define CL_OUT_OF_RESOURCES                         -5
#define CL_OUT_OF_HOST_MEMORY                       -6
#define CL_PROFILING_INFO_NOT_AVAILABLE             -7
#define CL_MEM_COPY_OVERLAP                         -8
#define CL_IMAGE_FORMAT_MISMATCH                    -9
#define CL_IMAGE_FORMAT_NOT_SUPPORTED               -10
#define CL_BUILD_PROGRAM_FAILURE                    -11
#define CL_MAP_FAILURE                              -12
// introduced in version 1.1
#define CL_MISALIGNED_SUB_BUFFER_OFFSET             -13
#define CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST -14
// end introduction
// introduced in version 1.2
#define CL_COMPILE_PROGRAM_FAILURE                  -15
#define CL_LINKER_NOT_AVAILABLE                     -16
#define CL_LINK_PROGRAM_FAILURE                     -17
#define CL_DEVICE_PARTITION_FAILED                  -18
#define CL_KERNEL_ARG_INFO_NOT_AVAILABLE            -19
// end introduction

#define CL_INVALID_VALUE                            -30
#define CL_INVALID_DEVICE_TYPE                      -31
#define CL_INVALID_PLATFORM                         -32
#define CL_INVALID_DEVICE                           -33
#define CL_INVALID_CONTEXT                          -34
#define CL_INVALID_QUEUE_PROPERTIES                 -35
#define CL_INVALID_COMMAND_QUEUE                    -36
#define CL_INVALID_HOST_PTR                         -37
#define CL_INVALID_MEM_OBJECT                       -38
#define CL_INVALID_IMAGE_FORMAT_DESCRIPTOR          -39
#define CL_INVALID_IMAGE_SIZE                       -40
#define CL_INVALID_SAMPLER                          -41
#define CL_INVALID_BINARY                           -42
#define CL_INVALID_BUILD_OPTIONS                    -43
#define CL_INVALID_PROGRAM                          -44
#define CL_INVALID_PROGRAM_EXECUTABLE               -45
#define CL_INVALID_KERNEL_NAME                      -46
#define CL_INVALID_KERNEL_DEFINITION                -47
#define CL_INVALID_KERNEL                           -48
#define CL_INVALID_ARG_INDEX                        -49
#define CL_INVALID_ARG_VALUE                        -50
#define CL_INVALID_ARG_SIZE                         -51
#define CL_INVALID_KERNEL_ARGS                      -52
#define CL_INVALID_WORK_DIMENSION                   -53
#define CL_INVALID_WORK_GROUP_SIZE                  -54
#define CL_INVALID_WORK_ITEM_SIZE                   -55
#define CL_INVALID_GLOBAL_OFFSET                    -56
#define CL_INVALID_EVENT_WAIT_LIST                  -57
#define CL_INVALID_EVENT                            -58
#define CL_INVALID_OPERATION                        -59
#define CL_INVALID_GL_OBJECT                        -60
#define CL_INVALID_BUFFER_SIZE                      -61
#define CL_INVALID_MIP_LEVEL                        -62
#define CL_INVALID_GLOBAL_WORK_SIZE                 -63
// introduced in version 1.1
#define CL_INVALID_PROPERTY                         -64
// end introduction
// introduced in version 1.2
#define CL_INVALID_IMAGE_DESCRIPTOR                 -65
#define CL_INVALID_COMPILER_OPTIONS                 -66
#define CL_INVALID_LINKER_OPTIONS                   -67
#define CL_INVALID_DEVICE_PARTITION_COUNT           -68
// end introduction
// introduced in version 2.0
#define CL_INVALID_PIPE_SIZE                        -69
#define CL_INVALID_DEVICE_QUEUE                     -70
// end introduction
// introduced in version 2.2
#define CL_INVALID_SPEC_ID                          -71
#define CL_MAX_SIZE_RESTRICTION_EXCEEDED            -72
// end introduction

// Custom OpenCL error code extentions for helper code return values. These extentions take up the positive space of the int32, since no other error codes (even other extentions) take up that space.
#define CL_EXT_DLL_LOAD_FAILURE							1
#define CL_EXT_DLL_FUNC_BIND_FAILURE					2
//#define CL_EXT_DLL_FREE_FAILURE							3
#define CL_EXT_NO_PLATFORMS_FOUND						4
#define CL_EXT_NO_DEVICES_FOUND_ON_PLATFORM				5
#define CL_EXT_NO_DEVICES_FOUND							6

#define CL_EXT_FILE_OPEN_FAILED							7

#define CL_EXT_CREATE_PROGRAM_FAILED					8
#define CL_EXT_INSUFFICIENT_HOST_MEM					9
#define CL_EXT_GET_BUILD_LOG_FAILED						10
#define CL_EXT_BUILD_FAILED_WITH_BUILD_LOG				11
#define CL_EXT_BUILD_FAILED_WITHOUT_BUILD_LOG			12
#define CL_EXT_CREATE_KERNEL_FAILED						13
#define CL_EXT_GET_KERNEL_WORK_GROUP_INFO_FAILED		14

/* cl_platform_info */
#define CL_PLATFORM_PROFILE                         0x0900
#define CL_PLATFORM_VERSION                         0x0901
#define CL_PLATFORM_NAME                            0x0902
#define CL_PLATFORM_VENDOR                          0x0903
#define CL_PLATFORM_EXTENSIONS                      0x0904
// introduced in version 2.1
#define CL_PLATFORM_HOST_TIMER_RESOLUTION           0x0905
// end introduction
// introduced in version 3.0
#define CL_PLATFORM_NUMERIC_VERSION                 0x0906
#define CL_PLATFORM_EXTENSIONS_WITH_VERSION         0x0907
// end introduction

/* cl_device_type - bitfield */
#define CL_DEVICE_TYPE_DEFAULT                      (1 << 0)
#define CL_DEVICE_TYPE_CPU                          (1 << 1)
#define CL_DEVICE_TYPE_GPU                          (1 << 2)
#define CL_DEVICE_TYPE_ACCELERATOR                  (1 << 3)
// introduced in version 1.2
#define CL_DEVICE_TYPE_CUSTOM                       (1 << 4)
// end introduction
#define CL_DEVICE_TYPE_ALL                          0xFFFFFFFF

/* cl_device_info */
#define CL_DEVICE_TYPE                                   0x1000
#define CL_DEVICE_VENDOR_ID                              0x1001
#define CL_DEVICE_MAX_COMPUTE_UNITS                      0x1002
#define CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS               0x1003
#define CL_DEVICE_MAX_WORK_GROUP_SIZE                    0x1004
#define CL_DEVICE_MAX_WORK_ITEM_SIZES                    0x1005
#define CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR            0x1006
#define CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT           0x1007
#define CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT             0x1008
#define CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG            0x1009
#define CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT           0x100A
#define CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE          0x100B
#define CL_DEVICE_MAX_CLOCK_FREQUENCY                    0x100C
#define CL_DEVICE_ADDRESS_BITS                           0x100D
#define CL_DEVICE_MAX_READ_IMAGE_ARGS                    0x100E
#define CL_DEVICE_MAX_WRITE_IMAGE_ARGS                   0x100F
#define CL_DEVICE_MAX_MEM_ALLOC_SIZE                     0x1010
#define CL_DEVICE_IMAGE2D_MAX_WIDTH                      0x1011
#define CL_DEVICE_IMAGE2D_MAX_HEIGHT                     0x1012
#define CL_DEVICE_IMAGE3D_MAX_WIDTH                      0x1013
#define CL_DEVICE_IMAGE3D_MAX_HEIGHT                     0x1014
#define CL_DEVICE_IMAGE3D_MAX_DEPTH                      0x1015
#define CL_DEVICE_IMAGE_SUPPORT                          0x1016
#define CL_DEVICE_MAX_PARAMETER_SIZE                     0x1017
#define CL_DEVICE_MAX_SAMPLERS                           0x1018
#define CL_DEVICE_MEM_BASE_ADDR_ALIGN                    0x1019
#define CL_DEVICE_MIN_DATA_TYPE_ALIGN_SIZE               0x101A
#define CL_DEVICE_SINGLE_FP_CONFIG                       0x101B
#define CL_DEVICE_GLOBAL_MEM_CACHE_TYPE                  0x101C
#define CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE              0x101D
#define CL_DEVICE_GLOBAL_MEM_CACHE_SIZE                  0x101E
#define CL_DEVICE_GLOBAL_MEM_SIZE                        0x101F
#define CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE               0x1020
#define CL_DEVICE_MAX_CONSTANT_ARGS                      0x1021
#define CL_DEVICE_LOCAL_MEM_TYPE                         0x1022
#define CL_DEVICE_LOCAL_MEM_SIZE                         0x1023
#define CL_DEVICE_ERROR_CORRECTION_SUPPORT               0x1024
#define CL_DEVICE_PROFILING_TIMER_RESOLUTION             0x1025
#define CL_DEVICE_ENDIAN_LITTLE                          0x1026
#define CL_DEVICE_AVAILABLE                              0x1027
#define CL_DEVICE_COMPILER_AVAILABLE                     0x1028
#define CL_DEVICE_EXECUTION_CAPABILITIES                 0x1029
// introduced in version 2.0
#define CL_DEVICE_QUEUE_ON_HOST_PROPERTIES               0x102A
// end introduction
#define CL_DEVICE_NAME                                   0x102B
#define CL_DEVICE_VENDOR                                 0x102C
#define CL_DRIVER_VERSION                                0x102D
#define CL_DEVICE_PROFILE                                0x102E
#define CL_DEVICE_VERSION                                0x102F
#define CL_DEVICE_EXTENSIONS                             0x1030
#define CL_DEVICE_PLATFORM                               0x1031
// introduced in version 1.2
#define CL_DEVICE_DOUBLE_FP_CONFIG                       0x1032
// end introduction

/* 0x1033 reserved for CL_DEVICE_HALF_FP_CONFIG which is already defined in "cl_ext.h" */	// <-- This comment was in the original OpenCL SDK header.

// introduced in version 1.1
#define CL_DEVICE_PREFERRED_VECTOR_WIDTH_HALF            0x1034
#define CL_DEVICE_NATIVE_VECTOR_WIDTH_CHAR               0x1036
#define CL_DEVICE_NATIVE_VECTOR_WIDTH_SHORT              0x1037
#define CL_DEVICE_NATIVE_VECTOR_WIDTH_INT                0x1038
#define CL_DEVICE_NATIVE_VECTOR_WIDTH_LONG               0x1039
#define CL_DEVICE_NATIVE_VECTOR_WIDTH_FLOAT              0x103A
#define CL_DEVICE_NATIVE_VECTOR_WIDTH_DOUBLE             0x103B
#define CL_DEVICE_NATIVE_VECTOR_WIDTH_HALF               0x103C
#define CL_DEVICE_OPENCL_C_VERSION                       0x103D
// end introduction
// introduced in version 1.2
#define CL_DEVICE_LINKER_AVAILABLE                       0x103E
#define CL_DEVICE_BUILT_IN_KERNELS                       0x103F
#define CL_DEVICE_IMAGE_MAX_BUFFER_SIZE                  0x1040
#define CL_DEVICE_IMAGE_MAX_ARRAY_SIZE                   0x1041
#define CL_DEVICE_PARENT_DEVICE                          0x1042
#define CL_DEVICE_PARTITION_MAX_SUB_DEVICES              0x1043
#define CL_DEVICE_PARTITION_PROPERTIES                   0x1044
#define CL_DEVICE_PARTITION_AFFINITY_DOMAIN              0x1045
#define CL_DEVICE_PARTITION_TYPE                         0x1046
#define CL_DEVICE_REFERENCE_COUNT                        0x1047
#define CL_DEVICE_PREFERRED_INTEROP_USER_SYNC            0x1048
#define CL_DEVICE_PRINTF_BUFFER_SIZE                     0x1049
// end introduction
// introduced in version 2.0
#define CL_DEVICE_IMAGE_PITCH_ALIGNMENT                  0x104A
#define CL_DEVICE_IMAGE_BASE_ADDRESS_ALIGNMENT           0x104B
#define CL_DEVICE_MAX_READ_WRITE_IMAGE_ARGS              0x104C
#define CL_DEVICE_MAX_GLOBAL_VARIABLE_SIZE               0x104D
#define CL_DEVICE_QUEUE_ON_DEVICE_PROPERTIES             0x104E
#define CL_DEVICE_QUEUE_ON_DEVICE_PREFERRED_SIZE         0x104F
#define CL_DEVICE_QUEUE_ON_DEVICE_MAX_SIZE               0x1050
#define CL_DEVICE_MAX_ON_DEVICE_QUEUES                   0x1051
#define CL_DEVICE_MAX_ON_DEVICE_EVENTS                   0x1052
#define CL_DEVICE_SVM_CAPABILITIES                       0x1053
#define CL_DEVICE_GLOBAL_VARIABLE_PREFERRED_TOTAL_SIZE   0x1054
#define CL_DEVICE_MAX_PIPE_ARGS                          0x1055
#define CL_DEVICE_PIPE_MAX_ACTIVE_RESERVATIONS           0x1056
#define CL_DEVICE_PIPE_MAX_PACKET_SIZE                   0x1057
#define CL_DEVICE_PREFERRED_PLATFORM_ATOMIC_ALIGNMENT    0x1058
#define CL_DEVICE_PREFERRED_GLOBAL_ATOMIC_ALIGNMENT      0x1059
#define CL_DEVICE_PREFERRED_LOCAL_ATOMIC_ALIGNMENT       0x105A
// end introduction
// introduced in 2.1
#define CL_DEVICE_IL_VERSION                             0x105B
#define CL_DEVICE_MAX_NUM_SUB_GROUPS                     0x105C
#define CL_DEVICE_SUB_GROUP_INDEPENDENT_FORWARD_PROGRESS 0x105D
// end introduction
// introduced in version 3.0
#define CL_DEVICE_NUMERIC_VERSION                        0x105E
#define CL_DEVICE_EXTENSIONS_WITH_VERSION                0x1060
#define CL_DEVICE_ILS_WITH_VERSION                       0x1061
#define CL_DEVICE_BUILT_IN_KERNELS_WITH_VERSION          0x1062
#define CL_DEVICE_ATOMIC_MEMORY_CAPABILITIES             0x1063
#define CL_DEVICE_ATOMIC_FENCE_CAPABILITIES              0x1064
#define CL_DEVICE_NON_UNIFORM_WORK_GROUP_SUPPORT         0x1065
#define CL_DEVICE_OPENCL_C_ALL_VERSIONS                  0x1066
#define CL_DEVICE_PREFERRED_WORK_GROUP_SIZE_MULTIPLE     0x1067
#define CL_DEVICE_WORK_GROUP_COLLECTIVE_FUNCTIONS_SUPPORT 0x1068
#define CL_DEVICE_GENERIC_ADDRESS_SPACE_SUPPORT          0x1069
/* 0x106A to 0x106E - Reserved for upcoming KHR extension */	// <-- This comment was in the original OpenCL SDK header.
#define CL_DEVICE_OPENCL_C_FEATURES                      0x106F
#define CL_DEVICE_DEVICE_ENQUEUE_CAPABILITIES            0x1070
#define CL_DEVICE_PIPE_SUPPORT                           0x1071
#define CL_DEVICE_LATEST_CONFORMANCE_VERSION_PASSED      0x1072
// end introduction

/* cl_mem_flags and cl_svm_mem_flags - bitfield */
#define CL_MEM_READ_WRITE                           (1 << 0)
#define CL_MEM_WRITE_ONLY                           (1 << 1)
#define CL_MEM_READ_ONLY                            (1 << 2)
#define CL_MEM_USE_HOST_PTR                         (1 << 3)
#define CL_MEM_ALLOC_HOST_PTR                       (1 << 4)
#define CL_MEM_COPY_HOST_PTR                        (1 << 5)
/* reserved                                         (1 << 6)    */	// <-- This comment was in the original OpenCL SDK header.
// introduced in version 1.2
#define CL_MEM_HOST_WRITE_ONLY                      (1 << 7)
#define CL_MEM_HOST_READ_ONLY                       (1 << 8)
#define CL_MEM_HOST_NO_ACCESS                       (1 << 9)
// end introduction
// introduced in version 2.0
#define CL_MEM_SVM_FINE_GRAIN_BUFFER                (1 << 10)   /* used by cl_svm_mem_flags only */	// <-- This comment was in the original OpenCL SDK header.
#define CL_MEM_SVM_ATOMICS                          (1 << 11)   /* used by cl_svm_mem_flags only */	// <-- This one too.
#define CL_MEM_KERNEL_READ_AND_WRITE                (1 << 12)
// end introduction

/* cl_channel_order */
#define CL_R                                        0x10B0											// Order of the channels when creating an image.
#define CL_A                                        0x10B1
#define CL_RG                                       0x10B2
#define CL_RA                                       0x10B3
#define CL_RGB                                      0x10B4
#define CL_RGBA                                     0x10B5
#define CL_BGRA                                     0x10B6
#define CL_ARGB                                     0x10B7
#define CL_INTENSITY                                0x10B8
#define CL_LUMINANCE                                0x10B9
// introduced in version 1.1
#define CL_Rx                                       0x10BA
#define CL_RGx                                      0x10BB
#define CL_RGBx                                     0x10BC
// end introduction
// introduced in version 1.2
#define CL_DEPTH                                    0x10BD
#define CL_DEPTH_STENCIL                            0x10BE
// end introduction
// introduced in version 2.0
#define CL_sRGB                                     0x10BF
#define CL_sRGBx                                    0x10C0
#define CL_sRGBA                                    0x10C1
#define CL_sBGRA                                    0x10C2
#define CL_ABGR                                     0x10C3
// end introduction


/* cl_channel_type */
#define CL_SNORM_INT8                               0x10D0
#define CL_SNORM_INT16                              0x10D1
#define CL_UNORM_INT8                               0x10D2
#define CL_UNORM_INT16                              0x10D3
#define CL_UNORM_SHORT_565                          0x10D4
#define CL_UNORM_SHORT_555                          0x10D5
#define CL_UNORM_INT_101010                         0x10D6
#define CL_SIGNED_INT8                              0x10D7
#define CL_SIGNED_INT16                             0x10D8
#define CL_SIGNED_INT32                             0x10D9
#define CL_UNSIGNED_INT8                            0x10DA
#define CL_UNSIGNED_INT16                           0x10DB
#define CL_UNSIGNED_INT32                           0x10DC
#define CL_HALF_FLOAT                               0x10DD
#define CL_FLOAT                                    0x10DE
// introduced in version 1.2
#define CL_UNORM_INT24                              0x10DF
// end introduction
// introduced in version 2.1
#define CL_UNORM_INT_101010_2                       0x10E0
// end introduction

/* cl_program_build_info */
#define CL_PROGRAM_BUILD_STATUS                     0x1181
#define CL_PROGRAM_BUILD_OPTIONS                    0x1182
#define CL_PROGRAM_BUILD_LOG                        0x1183
// introduced in version 1.2
#define CL_PROGRAM_BINARY_TYPE                      0x1184
// end introduction
// introduced in version 2.0
#define CL_PROGRAM_BUILD_GLOBAL_VARIABLE_TOTAL_SIZE 0x1185
// end introduction

/* cl_kernel_work_group_info */
#define CL_KERNEL_WORK_GROUP_SIZE						0x11B0
#define CL_KERNEL_COMPILE_WORK_GROUP_SIZE				0x11B1
#define CL_KERNEL_LOCAL_MEM_SIZE						0x11B2
#define CL_KERNEL_PREFERRED_WORK_GROUP_SIZE_MULTIPLE	0x11B3
#define CL_KERNEL_PRIVATE_MEM_SIZE						0x11B4
// introduced in version 1.2
#define CL_KERNEL_GLOBAL_WORK_SIZE						0x11B5
// end introduction

// Simple type definitions for basic fixed-width, OpenCL compatible types.
typedef int32_t cl_int;
typedef uint32_t cl_uint;
typedef uint64_t cl_ulong;
typedef cl_uint cl_bool;										// WARNING: For some reason, this is not guaranteed to be the same size as bools in the kernel. Kernel bools can have variable sizes depending on platform I guess.
typedef cl_ulong cl_bitfield;

// Platforms
typedef struct _cl_platform_id* cl_platform_id;
typedef cl_uint cl_platform_info;

// Devices
typedef cl_bitfield cl_device_type;
typedef struct _cl_device_id* cl_device_id;
typedef cl_uint cl_device_info;

// Contexts
typedef struct _cl_context* cl_context;
typedef intptr_t cl_context_properties;

// Command queues
typedef struct _cl_command_queue* cl_command_queue;
typedef cl_bitfield cl_command_queue_properties;

// Programs
typedef struct _cl_program* cl_program;
typedef cl_uint cl_program_build_info;

// Kernels
typedef struct _cl_kernel* cl_kernel;
typedef cl_uint cl_kernel_work_group_info;

// Memory
typedef struct _cl_mem* cl_mem;
typedef cl_bitfield cl_mem_flags;

// Image format
typedef cl_uint             cl_channel_order;
typedef cl_uint             cl_channel_type;

// Events
typedef struct _cl_event* cl_event;

// Image format struct
struct cl_image_format {
	cl_channel_order image_channel_order;
	cl_channel_type image_channel_data_type;
};

typedef cl_int (CL_API_CALL* clGetPlatformIDs_func)(cl_uint num_entries, 
													cl_platform_id* platforms, 
													cl_uint* num_platforms);
// Gets all of the availables platform IDs on the system.
inline clGetPlatformIDs_func clGetPlatformIDs;

typedef cl_int (CL_API_CALL* clGetPlatformInfo_func)(cl_platform_id platform, 
													 cl_platform_info param_name, 
													 size_t param_value_size, 
													 void* param_value, 
													 size_t* param_value_size_ret);
// Gets platform info for a specific platform.
inline clGetPlatformInfo_func clGetPlatformInfo;

typedef cl_int (CL_API_CALL* clGetDeviceIDs_func)(cl_platform_id platform, 
												  cl_device_type device_type, 
												  cl_uint num_entries, 
												  cl_device_id* devices, 
												  cl_uint* num_devices);
// Gets all the available device IDs on a specific platform.
inline clGetDeviceIDs_func clGetDeviceIDs;

typedef cl_int (CL_API_CALL* clGetDeviceInfo_func)(cl_device_id device, 
												   cl_device_info param_name, 
												   size_t param_value_size, 
												   void* param_value, 
												   size_t* param_value_size_ret);
// Gets device info for a specific device.
inline clGetDeviceInfo_func clGetDeviceInfo;

typedef cl_context (CL_API_CALL* clCreateContext_func)(const cl_context_properties* properties, 
													   cl_uint num_devices, 
													   const cl_device_id* devices, 
													   void (CL_CALLBACK* pfn_notify)(const char* errinfo, const void* private_info, size_t cb, void* user_data), 
													   void* user_data, 
													   cl_int* errcode_ret);
// Creates an OpenCL context. I assume this holds data which is useful for later functions. It would make sense if they work on the context like a state machine.
inline clCreateContext_func clCreateContext;

typedef cl_command_queue (CL_API_CALL* clCreateCommandQueue_func)(cl_context context, 
																  cl_device_id device, 
																  cl_command_queue_properties properties, 
																  cl_int* errcode_ret);
// Creates a command queue. This queue holds commands that will be executed sequentially. This is useful because these commands can run parallel to main code.
inline clCreateCommandQueue_func clCreateCommandQueue;

typedef cl_program (CL_API_CALL* clCreateProgramWithSource_func)(cl_context context, 
																 cl_uint count, 
																 const char* const* strings, 
																 const size_t* lengths, 
																 cl_int* errcode_ret);
// Creates an OpenCL program with the specified source.
inline clCreateProgramWithSource_func clCreateProgramWithSource;

typedef cl_int (CL_API_CALL* clBuildProgram_func)(cl_program program, 
												  cl_uint num_devices, 
												  const cl_device_id* device_list, 
												  const char* options, 
												  void (CL_CALLBACK* pfn_notify)(cl_program program, void* user_data), 
												  void* user_data);
// Builds an OpenCL program which was created with clCreateProgramWithSource.
inline clBuildProgram_func clBuildProgram;

typedef cl_int (CL_API_CALL* clGetProgramBuildInfo_func)(cl_program program, 
														 cl_device_id device, 
														 cl_program_build_info param_name, 
														 size_t param_value_size, 
														 void* param_value, 
														 size_t* param_value_size_ret);
// Gets build info about a built program. Useful for getting build logs of builds that didn't complete because of some error. This is the main tool when debugging kernels.
inline clGetProgramBuildInfo_func clGetProgramBuildInfo;

typedef cl_kernel (CL_API_CALL* clCreateKernel_func)(cl_program program, 
													 const char* kernel_name, 
													 cl_int* errcode_ret);
// Creates an OpenCL kernel using the successfully built program. A program can contain multiple kernels if I'm not mistaken, which is why this is necessary.
inline clCreateKernel_func clCreateKernel;

typedef cl_mem (CL_API_CALL* clCreateBuffer_func)(cl_context context, 
												  cl_mem_flags flags, 
												  size_t size, 
												  void* host_ptr, 
												  cl_int* errcode_ret);
// Creates a buffer on the device.
inline clCreateBuffer_func clCreateBuffer;

typedef cl_mem (CL_API_CALL* clCreateImage2D_func)(cl_context context, 
												   cl_mem_flags flags, 
												   const cl_image_format* image_format, 
												   size_t image_width, 
												   size_t image_height, 
												   size_t image_row_pitch, 
												   void* host_ptr, 
												   cl_int* errcode_ret);
// Creates a 2D image. This is essentially the same thing as a normal buffer, except you can access it in 2D and it contains various image channels (RGBA and such).
inline clCreateImage2D_func clCreateImage2D;

typedef cl_int (CL_API_CALL* clSetKernelArg_func)(cl_kernel kernel, 
												  cl_uint arg_index, 
												  size_t arg_size, 
												  const void* arg_value);
// Sets kernel arguments.
inline clSetKernelArg_func clSetKernelArg;

typedef cl_int (CL_API_CALL* clGetKernelWorkGroupInfo_func)(cl_kernel kernel, 
															cl_device_id device, 
															cl_kernel_work_group_info param_name, 
															size_t param_value_size, 
															void* param_value, 
															size_t* param_value_size_ret);
// Gets kernel work group info. Things like the optimal work group multiple and maximum work group size (based on the kernel memory usage and such) can be gotten.
inline clGetKernelWorkGroupInfo_func clGetKernelWorkGroupInfo;

typedef cl_int (CL_API_CALL* clEnqueueNDRangeKernel_func)(cl_command_queue command_queue, 
														  cl_kernel kernel, 
														  cl_uint work_dim, 
														  const size_t* global_work_offset, 
														  const size_t* global_work_size, 
														  const size_t* local_work_size, 
														  cl_uint num_events_in_wait_list, 
														  const cl_event* event_wait_list, 
														  cl_event* event);
// Enqueues a kernel on the command queue. There is no way to make this synchronous, you just have to use clFinish afterwards if you want to wait until it finishes.
inline clEnqueueNDRangeKernel_func clEnqueueNDRangeKernel;

typedef cl_int (CL_API_CALL* clFlush_func)(cl_command_queue command_queue);
// Flushes the command queue. That is to say it dispatches all the queued tasks.
inline clFlush_func clFlush;

typedef cl_int (CL_API_CALL* clFinish_func)(cl_command_queue command_queue);
// Waits for every entry in the command queue to finish (implicitly flushes before waiting). You can use this to synchronize OpenCL tasks with your own tasks.
inline clFinish_func clFinish;

typedef cl_int (CL_API_CALL* clEnqueueWriteBuffer_func)(cl_command_queue command_queue, 
														cl_mem buffer, 
														cl_bool blocking_write, 
														size_t offset, 
														size_t size, 
														const void* ptr, 
														cl_uint num_events_in_wait_list, 
														const cl_event* event_wait_list, 
														cl_event* event);
// Enqueues a buffer write on the command queue. You can set the blocking_write flag in order to wait for this function to finish without using clFinish.
inline clEnqueueWriteBuffer_func clEnqueueWriteBuffer;

typedef cl_int (CL_API_CALL* clEnqueueReadBuffer_func)(cl_command_queue command_queue, 
													   cl_mem buffer, 
													   cl_bool blocking_read, 
													   size_t offset, 
													   size_t size, 
													   void* ptr, 
													   cl_uint num_events_in_wait_list, 
													   const cl_event* event_wait_list, 
													   cl_event* event);
// Enqueues a buffer read on the command queue. You can set the blocking_read flag in order to wait for this function to finish without using clFinish.
inline clEnqueueReadBuffer_func clEnqueueReadBuffer;

typedef cl_int (CL_API_CALL* clEnqueueWriteImage_func)(cl_command_queue command_queue, 
													   cl_mem image, 
													   cl_bool blocking_write, 
													   const size_t* origin, 
													   const size_t* region, 
													   size_t input_row_pitch, 
													   size_t input_slice_pitch, 
													   const void* ptr, 
													   cl_uint num_events_in_wait_list, 
													   const cl_event* event_wait_list, 
													   cl_event* event);
// Enqueues an image write on the command queue. You can set the blocking_write flag in order to wait for this function to finish without using clFinish.
inline clEnqueueWriteImage_func clEnqueueWriteImage;

typedef cl_int (CL_API_CALL* clEnqueueReadImage_func)(cl_command_queue command_queue, 
													  cl_mem image, 
													  cl_bool blocking_read, 
													  const size_t* origin, 
													  const size_t* region, 
													  size_t row_pitch, 
													  size_t slice_pitch, 
													  void* ptr, 
													  cl_uint num_events_in_wait_list, 
													  const cl_event* event_wait_list, 
													  cl_event* event);
// Enqueues an image read on the command queue. You can set the blocking_read flag in order to wait for this function to finish without using clFinish.
inline clEnqueueReadImage_func clEnqueueReadImage;

typedef cl_int (CL_API_CALL* clReleaseMemObject_func)(cl_mem memobj);
// Decrements a memory object's reference count.
inline clReleaseMemObject_func clReleaseMemObject;

typedef cl_int (CL_API_CALL* clReleaseKernel_func)(cl_kernel kernel);
// Decrements a kernel's reference count.
inline clReleaseKernel_func clReleaseKernel;

typedef cl_int (CL_API_CALL* clReleaseProgram_func)(cl_program program);
// Decrements a program's reference count.
inline clReleaseProgram_func clReleaseProgram;

typedef cl_int (CL_API_CALL* clReleaseCommandQueue_func)(cl_command_queue command_queue);
// Decrements a command queue's reference count.
inline clReleaseCommandQueue_func clReleaseCommandQueue;

typedef cl_int (CL_API_CALL* clReleaseContext_func)(cl_context context);
// Decrements a context's reference count.
inline clReleaseContext_func clReleaseContext;

// Stores version information in numerical form.
struct VersionIdentifier {
	uint16_t major;
	uint16_t minor;

	VersionIdentifier(uint16_t major, uint16_t minor);

	bool operator>=(const VersionIdentifier& rightSide);
};

class OpenCLDeviceCollection {
public:
	cl_context* contexts = nullptr;
	size_t* contextEndIndices = nullptr;
	size_t contexts_length;
	cl_device_id* devices = nullptr;
	size_t devices_length;

	constexpr OpenCLDeviceCollection() noexcept : devices_length(0), contexts_length(0) { }

	constexpr OpenCLDeviceCollection(cl_int err, size_t contexts_length, size_t devices_length) noexcept : devices_length(devices_length), contexts_length(contexts_length) {
		devices = new (std::nothrow) cl_device_id[devices_length];
		if (!devices) { err = 0; return; }			// TODO: Make this actually return the right error codes.
		contexts = new (std::nothrow) cl_context[contexts_length];
		if (!contexts) { delete[] devices; err = 0; return; }
		contextEndIndices = new (std::nothrow) size_t[contexts_length];
		if (!contextEndIndices) { delete[] contexts; delete[] devices; err = 0; return; }
	}

	OpenCLDeviceCollection(const OpenCLDeviceCollection& right) = delete;
	// SIDE-NOTE: Move constructor is deleted automatically if copy constructor is deleted.
	
	constexpr OpenCLDeviceCollection(OpenCLDeviceCollection&& right) noexcept : 
		contexts(right.contexts), contextEndIndices(right.contextEndIndices), contexts_length(right.contexts_length), 
		devices(right.devices), devices_length(right.devices_length)
	{
		right.contexts = nullptr;
		right.contextEndIndices = nullptr;
		right.devices = nullptr;
	}

	OpenCLDeviceCollection& operator=(const OpenCLDeviceCollection& right) = delete;
	// Move assignment operator is deleted automatically if copy assignment operator is deleted.

	constexpr void swap(OpenCLDeviceCollection& other) noexcept {
		cl_context* temp_contexts = contexts;
		contexts = other.contexts;
		other.contexts = temp_contexts;

		size_t* temp_contextEndIndices = contextEndIndices;
		contextEndIndices = other.contextEndIndices;
		other.contextEndIndices = contextEndIndices;

		size_t temp_contexts_length = contexts_length;
		contexts_length = other.contexts_length;
		other.contexts_length = temp_contexts_length;

		cl_device_id* temp_devices = devices;
		devices = other.devices;
		other.devices = temp_devices;

		size_t temp_devices_length = devices_length;
		devices_length = other.devices_length;
		other.devices_length = temp_devices_length;
	}

	constexpr OpenCLDeviceIndexCollection createDeviceIndexCollection(cl_int& err) const noexcept {
		return OpenCLDeviceIndexCollection(err, this, devices_length);
	}

	constexpr cl_device_id& operator[](size_t index) noexcept { return devices[index]; }

	constexpr cl_context& getContextForDeviceIndex(size_t deviceIndex) noexcept {			// TODO: Go over this binary search again and maek sure it is the most optimal it can be.
		size_t startIndex = 0;
		size_t endIndex = contexts_length;
		while (true) {
			size_t middle = endIndex / 2;
			if (deviceIndex < contextEndIndices[middle]) {
				if (middle == 0) { return contexts[0]; }
				if (deviceIndex >= contextEndIndices[middle - 1]) { return contexts[middle]; }
				endIndex = contextEndIndices[middle];
				continue;
			}
			if (deviceIndex > contextEndIndices[middle]) {
				if (deviceIndex >= contextEndIndices[middle - 1]) { return contexts[middle]; }
				startIndex = contextEndIndices[middle];
				continue;
			}
			return contexts[middle + 1];
		}
	}

	constexpr ~OpenCLDeviceCollection() noexcept {
		delete[] contextEndIndices;
		delete[] contexts;
		delete[] devices;
	}
};

class OpenCLDeviceIndexCollection {
	const OpenCLDeviceCollection* data;

public:
	size_t* indices = nullptr;
	size_t length;

	constexpr OpenCLDeviceIndexCollection() noexcept = default;

	constexpr OpenCLDeviceIndexCollection(cl_int& err, const OpenCLDeviceCollection* data, size_t length) noexcept : 
		data(data), length(length) 
	{
		indices = new (std::nothrow) size_t[length];
		if (!indices) { err = CL_EXT_INSUFFICIENT_HOST_MEM; }
	}

	constexpr OpenCLDeviceIndexCollection(cl_int& err, const OpenCLDeviceIndexCollection& right) noexcept : length(right.length) {
		indices = new (std::nothrow) size_t[length];
		if (!indices) { err = CL_EXT_INSUFFICIENT_HOST_MEM; }
	}

	constexpr OpenCLDeviceIndexCollection(const OpenCLDeviceIndexCollection& right) noexcept : length(right.length) {
		indices = new (std::nothrow) size_t[length];
	}

	constexpr OpenCLDeviceIndexCollection(OpenCLDeviceIndexCollection&& right) noexcept : length(right.length) {
		indices = right.indices;
		right.indices = nullptr;
	}

	OpenCLDeviceIndexCollection& operator=(const OpenCLDeviceIndexCollection& right) = delete;
	// Move assignment operator is deleted automatically if copy assignment operator is deleted.

	constexpr void swap(OpenCLDeviceIndexCollection& other) noexcept {
		const OpenCLDeviceCollection* temp_data = data;
		data = other.data;
		other.data = temp_data;

		size_t* temp_indices = indices;
		indices = other.indices;
		other.indices = temp_indices;

		size_t temp_length = length;
		length = other.length;
		other.length = temp_length;
	}

	constexpr OpenCLDeviceIndexCollection removeDevicesOfType(cl_device_type computeDeviceType) const noexcept {

	}

	constexpr OpenCLDeviceIndexCollection removeDevicesNotOfType(cl_device_type computeDeviceType) const noexcept {

	}

	constexpr OpenCLDeviceIndexCollection sortByWorkGroupSize() const noexcept {

	}

	constexpr ~OpenCLDeviceIndexCollection() noexcept {
		delete[] indices;		// Doesn't set indices to nullptr, but that doesn't matter in this case.
	}
};

// Bind a specific DLL function to it's corresponding function pointer. Splitting these up into separate functions is useful in case the user wants to bind these in a lazy fashion.
bool bind_clGetPlatformIDs();
bool bind_clGetPlatformInfo();
bool bind_clGetDeviceIDs();
bool bind_clGetDeviceInfo();
bool bind_clCreateContext();
bool bind_clCreateCommandQueue();
bool bind_clCreateProgramWithSource();
bool bind_clBuildProgram();
bool bind_clGetProgramBuildInfo();
bool bind_clCreateKernel();
bool bind_clCreateBuffer();
bool bind_clCreateImage2D();
bool bind_clSetKernelArg();
bool bind_clGetKernelWorkGroupInfo();
bool bind_clEnqueueNDRangeKernel();
bool bind_clFinish();
bool bind_clEnqueueWriteBuffer();
bool bind_clEnqueueReadBuffer();
bool bind_clEnqueueWriteImage();
bool bind_clEnqueueReadImage();
bool bind_clReleaseMemObject();
bool bind_clReleaseKernel();
bool bind_clReleaseProgram();
bool bind_clReleaseCommandQueue();
bool bind_clReleaseContext();

bool loadOpenCLLib();

// Simple helper function which initializes the dynamic linkage to the OpenCL DLL and initializes the bindings to all of the various functions.
cl_int initOpenCLBindings();

bool freeOpenCLLib();

VersionIdentifier convertOpenCLVersionStringToVersionIdentifier(const char* string);

// TODO: Consider putting all this opencl stuff in a namespace to avoid collisions and messiness.

OpenCLDeviceCollection getAllOpenCLDevices(cl_int& err, const VersionIdentifier& minimumPlatformVersion);

// Finds the most optimal device in the available list of devices on the system and initializes basic OpenCL variables based on that device.
// NOTE: In case you want to only bind the functions that this function uses, it uses:
// clGetPlatformIDs
// clGetPlatformInfo
// clGetDeviceIDs
// clGetDeviceInfo
// clCreateContext
// clCreateCommandQueue
// clReleaseContext
// TODO: Update the name of minPlatVers in the implementation as well.
cl_int initOpenCLVarsForBestDevice(const VersionIdentifier& minimumPlatformVersion, cl_platform_id& bestPlatform, cl_device_id& bestDevice, cl_context& context, cl_command_queue& commandQueue);

// Helper function to quickly set up a compute kernel.
// NOTE: In case you want to only bind the functions that this function uses, it uses:
// clCreateProgramWithSource
// clBuildProgram
// clGetProgramBuildInfo
// clReleaseProgram
// clCreateKernel
// clGetKernelWorkGroupInfo
// clReleaseKernel
// TODO: Annotate these two functions properly.
cl_int setupComputeKernelFromString(cl_context context, cl_device_id device, const char* sourceCodeString, const char* kernelName, cl_program& program, cl_kernel& kernel, size_t& kernelWorkGroupSize, std::string& buildLog);
cl_int setupComputeKernelFromFile(cl_context context, cl_device_id device, const char* sourceCodeFile, const char* kernelName, cl_program& program, cl_kernel& kernel, size_t& kernelWorkGroupSize, std::string& buildLog);
