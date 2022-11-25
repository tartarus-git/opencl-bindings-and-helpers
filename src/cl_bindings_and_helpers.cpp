#include "../include/cl_bindings_and_helpers.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <cstdint>						// For fixed-width types.

#include <new>							// For std::nothrow.

#include <vector>

#include <fstream>						// For reading OpenCL source code from file.

#include <string>						// For std::string.

#include <limits>						// for std::numeric_limits

HMODULE DLLHandle;

bool loadOpenCLLib() noexcept { return DLLHandle = LoadLibraryA("OpenCL.dll"); }

bool bind_clGetPlatformIDs() { return clGetPlatformIDs = (clGetPlatformIDs_func)GetProcAddress(DLLHandle, "clGetPlatformIDs"); }
bool bind_clGetPlatformInfo() { return clGetPlatformInfo = (clGetPlatformInfo_func)GetProcAddress(DLLHandle, "clGetPlatformInfo"); }
bool bind_clGetDeviceIDs() { return clGetDeviceIDs = (clGetDeviceIDs_func)GetProcAddress(DLLHandle, "clGetDeviceIDs"); }
bool bind_clGetDeviceInfo() { return clGetDeviceInfo = (clGetDeviceInfo_func)GetProcAddress(DLLHandle, "clGetDeviceInfo"); }
bool bind_clCreateContext() { return clCreateContext = (clCreateContext_func)GetProcAddress(DLLHandle, "clCreateContext"); }
bool bind_clGetContextInfo() { return clGetContextInfo = (clGetContextInfo_func)GetProcAddress(DLLHandle, "clGetContextInfo"); }
bool bind_clCreateCommandQueue() { return clCreateCommandQueue = (clCreateCommandQueue_func)GetProcAddress(DLLHandle, "clCreateCommandQueue"); }
bool bind_clCreateProgramWithSource() { return clCreateProgramWithSource = (clCreateProgramWithSource_func)GetProcAddress(DLLHandle, "clCreateProgramWithSource"); }
bool bind_clBuildProgram() { return clBuildProgram = (clBuildProgram_func)GetProcAddress(DLLHandle, "clBuildProgram"); }
bool bind_clGetProgramBuildInfo() { return clGetProgramBuildInfo = (clGetProgramBuildInfo_func)GetProcAddress(DLLHandle, "clGetProgramBuildInfo"); }
bool bind_clCreateKernel() { return clCreateKernel = (clCreateKernel_func)GetProcAddress(DLLHandle, "clCreateKernel"); }
bool bind_clCreateBuffer() { return clCreateBuffer = (clCreateBuffer_func)GetProcAddress(DLLHandle, "clCreateBuffer"); }
bool bind_clCreateImage2D() { return clCreateImage2D = (clCreateImage2D_func)GetProcAddress(DLLHandle, "clCreateImage2D"); }
bool bind_clSetKernelArg() { return clSetKernelArg = (clSetKernelArg_func)GetProcAddress(DLLHandle, "clSetKernelArg"); }
bool bind_clGetKernelWorkGroupInfo() { return clGetKernelWorkGroupInfo = (clGetKernelWorkGroupInfo_func)GetProcAddress(DLLHandle, "clGetKernelWorkGroupInfo"); }
bool bind_clEnqueueNDRangeKernel() { return clEnqueueNDRangeKernel = (clEnqueueNDRangeKernel_func)GetProcAddress(DLLHandle, "clEnqueueNDRangeKernel"); }
bool bind_clFlush() { return clFlush = (clFlush_func)GetProcAddress(DLLHandle, "clFlush"); }
bool bind_clFinish() { return clFinish = (clFinish_func)GetProcAddress(DLLHandle, "clFinish"); }
bool bind_clEnqueueWriteBuffer() { return clEnqueueWriteBuffer = (clEnqueueWriteBuffer_func)GetProcAddress(DLLHandle, "clEnqueueWriteBuffer"); }
bool bind_clEnqueueReadBuffer() { return clEnqueueReadBuffer = (clEnqueueReadBuffer_func)GetProcAddress(DLLHandle, "clEnqueueReadBuffer"); }
bool bind_clEnqueueWriteImage() { return clEnqueueWriteImage = (clEnqueueWriteImage_func)GetProcAddress(DLLHandle, "clEnqueueWriteImage"); }
bool bind_clEnqueueReadImage() { return clEnqueueReadImage = (clEnqueueReadImage_func)GetProcAddress(DLLHandle, "clEnqueueReadImage"); }
bool bind_clReleaseMemObject() { return clReleaseMemObject = (clReleaseMemObject_func)GetProcAddress(DLLHandle, "clReleaseMemObject"); }
bool bind_clReleaseKernel() { return clReleaseKernel = (clReleaseKernel_func)GetProcAddress(DLLHandle, "clReleaseKernel"); }
bool bind_clReleaseProgram() { return clReleaseProgram = (clReleaseProgram_func)GetProcAddress(DLLHandle, "clReleaseProgram"); }
bool bind_clReleaseCommandQueue() { return clReleaseCommandQueue = (clReleaseCommandQueue_func)GetProcAddress(DLLHandle, "clReleaseCommandQueue"); }
bool bind_clReleaseContext() { return clReleaseContext = (clReleaseContext_func)GetProcAddress(DLLHandle, "clReleaseContext"); }

#define CHECK_FUNC_VALIDITY(func) if (!(func)) { FreeLibrary(DLLHandle); return CL_EXT_DLL_FUNC_BIND_FAILURE; }

cl_int initOpenCLBindings() noexcept {
	if (!loadOpenCLLib()) { return CL_EXT_DLL_LOAD_FAILURE; }

	CHECK_FUNC_VALIDITY(bind_clGetPlatformIDs());										// Go through all the functions and bind them one by one.
	CHECK_FUNC_VALIDITY(bind_clGetPlatformInfo());										// As soon as a bind fails, try to free the library and subsequently return failure for the whole init function.
	CHECK_FUNC_VALIDITY(bind_clGetDeviceIDs());
	CHECK_FUNC_VALIDITY(bind_clGetDeviceInfo());
	CHECK_FUNC_VALIDITY(bind_clCreateContext());
	CHECK_FUNC_VALIDITY(bind_clGetContextInfo());
	CHECK_FUNC_VALIDITY(bind_clCreateCommandQueue());
	CHECK_FUNC_VALIDITY(bind_clCreateProgramWithSource());
	CHECK_FUNC_VALIDITY(bind_clBuildProgram());
	CHECK_FUNC_VALIDITY(bind_clGetProgramBuildInfo());
	CHECK_FUNC_VALIDITY(bind_clCreateKernel());
	CHECK_FUNC_VALIDITY(bind_clCreateBuffer());
	CHECK_FUNC_VALIDITY(bind_clCreateImage2D());
	CHECK_FUNC_VALIDITY(bind_clSetKernelArg());
	CHECK_FUNC_VALIDITY(bind_clGetKernelWorkGroupInfo());
	CHECK_FUNC_VALIDITY(bind_clEnqueueNDRangeKernel());
	CHECK_FUNC_VALIDITY(bind_clFlush());
	CHECK_FUNC_VALIDITY(bind_clFinish());
	CHECK_FUNC_VALIDITY(bind_clEnqueueWriteBuffer());
	CHECK_FUNC_VALIDITY(bind_clEnqueueReadBuffer());
	CHECK_FUNC_VALIDITY(bind_clEnqueueWriteImage());
	CHECK_FUNC_VALIDITY(bind_clEnqueueReadImage());
	CHECK_FUNC_VALIDITY(bind_clReleaseMemObject());
	CHECK_FUNC_VALIDITY(bind_clReleaseKernel());
	CHECK_FUNC_VALIDITY(bind_clReleaseProgram());
	CHECK_FUNC_VALIDITY(bind_clReleaseCommandQueue());
	CHECK_FUNC_VALIDITY(bind_clReleaseContext());

	return CL_SUCCESS;
}

bool freeOpenCLLib() noexcept { return FreeLibrary(DLLHandle); }

// TODO: noexcept more things.

// NOTE: Assumes that the input is clean.
uint16_t convertStringToUInt16(const char* string, size_t length) {
	uint16_t result = string[0] - '0';
	for (int i = 1; i < length; i++) { result = result * 10 + (string[i] - '0'); }
	return result;
}

// NOTE: Assumes that the input is clean and there is at least one character of data to process and the string is null-terminated.
uint16_t convertStringToUInt16(const char* string) {
	uint16_t result = string[0] - '0';
	for (int i = 1; ; i++) { if (string[i] == '\0') { return result; } result = result * 10 + (string[i] - '0'); }
}

// NOTE: Assumes the version string is always valid and has at least one number character for both the major and the minor versions. Also obviously assumes the string is null-terminated.
VersionIdentifier convertOpenCLVersionStringToVersionIdentifier(const char* string) {
	for (int i = CL_EXT_VERSION_STRING_PREFIX_LENGTH; ; i++) {
		if (string[i] == '.') { return VersionIdentifier(convertStringToUInt16(string + CL_EXT_VERSION_STRING_PREFIX_LENGTH, i - CL_EXT_VERSION_STRING_PREFIX_LENGTH), convertStringToUInt16(string + i + 1)); }
		if (string[i] == '\0') { return VersionIdentifier(-1, -1); }			// This shouldn't happen given the requirements above, but I feel better knowing it's here.
	}
}

OpenCLDeviceCollection getAllOpenCLDevices(cl_int& err, const VersionIdentifier& minimumPlatformVersion) {
	cl_uint platformCount;
	err = clGetPlatformIDs(0, nullptr, &platformCount);
	if (err != CL_SUCCESS) { return OpenCLDeviceCollection(); }
	if (platformCount == 0) { err = CL_EXT_NO_PLATFORMS_FOUND; return OpenCLDeviceCollection(); }

	cl_platform_id* platforms = new (std::nothrow) cl_platform_id[platformCount];
	if (!platforms) {
		err = CL_EXT_INSUFFICIENT_HOST_MEM;
		return OpenCLDeviceCollection();
	}
	err = clGetPlatformIDs(platformCount, platforms, nullptr);
	if (err != CL_SUCCESS) {
		delete[] platforms;
		return OpenCLDeviceCollection();
	}

	custom_vector<cl_context> contexts(err);
	if (err != CL_SUCCESS) { delete[] platforms; return OpenCLDeviceCollection(); }

	custom_vector<size_t> context_end_indices(err);
	if (err != CL_SUCCESS) { delete[] platforms; return OpenCLDeviceCollection(); }

	custom_vector<cl_device_id> devices(err);
	if (err != CL_SUCCESS) { delete[] platforms; return OpenCLDeviceCollection(); }

	for (size_t i = 0; i < platformCount; i++) {
		const cl_platform_id& currentPlatform = platforms[i];										// NOTE: You might think you can just as well leave out the reference, but I think it is probably better with the reference since there are ways a copy can be avoided and we don't want to hinder that.
																									// NOTE: Although on second thought, this technique doesn't really do anything in this case since the compiler can easily optimize it even if we just use a copy.
		size_t versionStringSize;
		err = clGetPlatformInfo(currentPlatform, CL_PLATFORM_VERSION, 0, nullptr, &versionStringSize);
		if (err != CL_SUCCESS) {
			delete[] platforms;
			return OpenCLDeviceCollection();
		}

		char* versionString = new (std::nothrow) char[versionStringSize];
		if (!versionString) {
			err = CL_EXT_INSUFFICIENT_HOST_MEM;
			delete[] platforms;
			return OpenCLDeviceCollection();
		}
		err = clGetPlatformInfo(currentPlatform, CL_PLATFORM_VERSION, versionStringSize, versionString, nullptr);
		if (err != CL_SUCCESS) {
			delete[] versionString;
			delete[] platforms;
			return OpenCLDeviceCollection();
		}

		VersionIdentifier platform_version = convertOpenCLVersionStringToVersionIdentifier(versionString);
		delete[] versionString;

		if (platform_version >= minimumPlatformVersion) {
			cl_uint deviceCount;
			err = clGetDeviceIDs(currentPlatform, CL_DEVICE_TYPE_ALL, 0, nullptr, &deviceCount);
			switch (err) {
			case CL_SUCCESS: break;
			case CL_DEVICE_NOT_FOUND:
				err = CL_EXT_NO_DEVICES_FOUND_ON_PLATFORM;
				/*
				* NOTE: Since we're using CL_DEVICE_TYPE_ALL, there is no excuse for the existence of
				* a platform if we cannot see at least one device on it. We throw an error if it
				* happens so that the user knows something is wrong with his system.
				* (This shouldn't ever happen unless something is wrong with your system.)
				*/
			default:
				delete[] platforms;
				return OpenCLDeviceCollection();
			}
			if (deviceCount == 0) {
				/*
				* NOTE: deviceCount shouldn't ever be 0 for the same reason as the comment above explains, and doubly so because the CL_DEVICE_NOT_FOUND error already exists to handle this case.
				* Just in case though, since it doesn't hurt to check, we check for this case and return an error if it happens.
				* Something is almost definitely wrong with your system if this happens.
				*/
				err = CL_EXT_NO_DEVICES_FOUND_ON_PLATFORM;
				delete[] platforms;
				return OpenCLDeviceCollection();
			}

			const size_t before_length = devices.length;

			err = devices.push_empty_back(deviceCount);
			if (err != CL_SUCCESS) { delete[] platforms; return OpenCLDeviceCollection(); }

			err = clGetDeviceIDs(currentPlatform, CL_DEVICE_TYPE_ALL, deviceCount, devices.data + before_length, nullptr);
			if (err != CL_SUCCESS) { delete[] platforms; return OpenCLDeviceCollection(); }						// NOTE: This really shouldn't ever throw an error, see above comments.

			cl_context new_context = clCreateContext(nullptr, deviceCount, devices.data + before_length, nullptr, nullptr, &err);
			if (!new_context) { delete[] platforms; return OpenCLDeviceCollection(); }		// TODO: Handle err codes.

			err = contexts.push_back(new_context);
			if (err != CL_SUCCESS) { delete[] platforms; return OpenCLDeviceCollection(); }

			err = context_end_indices.push_back(devices.length);
			if (err != CL_SUCCESS) { delete[] platforms; return OpenCLDeviceCollection(); }

			// TODO: Accidentally reimplemented the thing above, remove all the stuff above and basically revert everything.
		}
	}

	/*
	* 
	* NOTE: We go through everything, get the counts, then construct the OpenCLDeviceCollection, go through everything again
	* and get the data. The reason we do this is because std::vector isn't able to lose control of it's data.
	* We could create our own std::vector (would be easy in this case since we barely use any of the functionality) and add
	* the functionality that we want, but this is easier. This solution is possibly minimally worse (can't definitively tell
	* until you benchmark it though), but this function is only run once so it's totally not a problem.
	* TODO: Maybe as a future improvement, consider trying it with a custom vector.
	* 
	*/

	size_t validPlatformsCount = validPlatforms.size();

	OpenCLDeviceCollection result(err, validPlatformsCount, totalDeviceCount);

	size_t lastContextEndIndex = 0;
	for (size_t i = 0; i < validPlatformsCount; i++) {
		cl_device_id* devicesStart = result.devices + lastContextEndIndex;
		err = clGetDeviceIDs(platforms[validPlatforms[i]], CL_DEVICE_TYPE_ALL, validPlatformDeviceCounts[i], devicesStart, nullptr);
		if (err != CL_SUCCESS) {
			delete[] platforms;
			return OpenCLDeviceCollection();
		}

		result.contexts[i] = clCreateContext(nullptr, validPlatformDeviceCounts[i], devicesStart, nullptr, nullptr, &err);
		if (err != CL_SUCCESS) {
			delete[] platforms;
			return OpenCLDeviceCollection();
		}

		lastContextEndIndex += validPlatformDeviceCounts[i];
		result.contextEndIndices[i] = lastContextEndIndex;
	}

	return result;
}

cl_int initOpenCLVarsForBestDevice(const VersionIdentifier& minimumTargetPlatformVersion, cl_platform_id& bestPlatform, cl_device_id& bestDevice, cl_context& context, cl_command_queue& commandQueue) {
	/*cl_uint platformCount;
	cl_int err = clGetPlatformIDs(0, nullptr, &platformCount);
	if (err != CL_SUCCESS) { return err; }
	if (!platformCount) { return CL_EXT_NO_PLATFORMS_FOUND; }

	cl_platform_id* platforms = new (std::nothrow) cl_platform_id[platformCount];
	if (!platforms) { return CL_EXT_INSUFFICIENT_HOST_MEM; }
	err = clGetPlatformIDs(platformCount, platforms, nullptr);
	if (err != CL_SUCCESS) { delete[] platforms; return err; }

	size_t bestDeviceMaxWorkGroupSize = 0;
	for (int i = 0; i < platformCount; i++) {
		const cl_platform_id& currentPlatform = platforms[i];										// NOTE: You might think you can just as well leave out the reference, but I think it is probably better with the reference since there are ways a copy can be avoided (stays in register the whole time for example) and we don't want to hinder that.
																									// NOTE: Although on second thought, this technique doesn't really do anything in this case since the compiler can easily optimize it even if we just use a copy. 
		size_t versionStringSize;
		err = clGetPlatformInfo(currentPlatform, CL_PLATFORM_VERSION, 0, nullptr, &versionStringSize);
		if (err != CL_SUCCESS) { delete[] platforms; return err; }

		char* versionString = new (std::nothrow) char[versionStringSize];
		if (!versionString) { delete[] platforms; return CL_EXT_INSUFFICIENT_HOST_MEM; }
		err = clGetPlatformInfo(currentPlatform, CL_PLATFORM_VERSION, versionStringSize, versionString, nullptr);
		if (err != CL_SUCCESS) { delete[] versionString; delete[] platforms; return err; }

		if (convertOpenCLVersionStringToVersionIdentifier(versionString) >= minimumTargetPlatformVersion) {
			delete[] versionString;

			cl_uint deviceCount;
			err = clGetDeviceIDs(currentPlatform, CL_DEVICE_TYPE_GPU, 0, nullptr, &deviceCount);				// TODO: Change this algorithm to work with any device that isn't the CPU, so also signal processors or whatever other accel thing you have connected to your computer.
			if (err != CL_SUCCESS) { delete[] platforms; return err; }
			if (!deviceCount) { delete[] platforms; return CL_EXT_NO_DEVICES_FOUND_ON_PLATFORM; }

			cl_device_id* devices = new (std::nothrow) cl_device_id[deviceCount];
			if (!devices) { delete[] platforms; return CL_EXT_INSUFFICIENT_HOST_MEM; }
			err = clGetDeviceIDs(currentPlatform, CL_DEVICE_TYPE_GPU, deviceCount, devices, nullptr);
			if (err != CL_SUCCESS) { delete[] platforms; return err; }

			for (int j = 0; j < deviceCount; j++) {
				cl_device_id& currentDevice = devices[i];

				size_t deviceMaxWorkGroupSize;																												// Get the theoretical maximum work group size of the current device. This value is how we measure which device has the most computational power, thereby qualifying as the best.
				err = clGetDeviceInfo(currentDevice, CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(size_t), &deviceMaxWorkGroupSize, nullptr);
				if (err != CL_SUCCESS) { delete[] platforms; return err; }

				if (deviceMaxWorkGroupSize > bestDeviceMaxWorkGroupSize) {
					bestDeviceMaxWorkGroupSize = deviceMaxWorkGroupSize;
					bestDevice = currentDevice;
					bestPlatform = currentPlatform;
				}
			}
			continue;
		}
		delete[] versionString;
	}
	delete[] platforms;
	if (!bestDeviceMaxWorkGroupSize) { return CL_EXT_NO_DEVICES_FOUND; }																					// NOTE: This error theoretically never ever gets thrown here, but I'm keeping it in just in case something crazy happens.

	// Establish other needed vars using the best device on the system.

	context = clCreateContext(nullptr, 1, &bestDevice, nullptr, nullptr, &err);
	if (err != CL_SUCCESS) { return err; }

	commandQueue = clCreateCommandQueue(context, bestDevice, 0, &err);
	if (err != CL_SUCCESS) {
		clReleaseContext(context);																															// Errors aren't handled here because it doesn't make a difference if it fails or not.
		return err;
	}

	return CL_SUCCESS;*/




	cl_int err;

	OpenCLDeviceCollection devices = getAllOpenCLDevices(err, minimumTargetPlatformVersion);
	if (err != CL_SUCCESS) { return err; }

	OpenCLDeviceIndexCollection deviceIndices = devices.createDeviceIndexCollection(err);
	if (err != CL_SUCCESS) { return err; }

	OpenCLDeviceIndexCollection sortedDeviceIndices = deviceIndices.sort_by_increasing_max_work_group_size(err);
	if (err != CL_SUCCESS) { return err; }

	bestDevice = devices[sortedDeviceIndices[sortedDeviceIndices.length - 1]];
	context = devices.getContextForDeviceIndex(sortedDeviceIndices[sortedDeviceIndices.length - 1]);

	commandQueue = clCreateCommandQueue(context, bestDevice, 0, &err);
	if (err != CL_SUCCESS) { return err; }

	/*
	size_t context_properties_size;
	err = clGetContextInfo(context, CL_CONTEXT_PROPERTIES, 0, nullptr, &context_properties_size);
	if (err != CL_SUCCESS) { return err; }

	cl_context_properties* context_properties = new (std::nothrow) cl_context_properties[context_properties_size];
	err = clGetContextInfo(context, CL_CONTEXT_PROPERTIES, context_properties_size, context_properties, nullptr);
	if (err != CL_SUCCESS) { return err; }

	for (size_t i = 0; i < context_properties_size; i += 2) {
		if (context_properties[i] == CL_CONTEXT_PLATFORM) {
			// NOTE: This is how I would've done it, if reintrepet_casting from char
			// would be allowed in the standard and if both types were the same width.
			// I've heard it's coming soon,
			// so maybe we could use this eventually.
			// NOTE: The reason I would've gone through char* is because or else it's
			// undefined behaviour. See strict aliasing or something I think.
			//bestPlatform = *(cl_platform_id*)(char*)&context_properties[i + 1];
			// NOTE: Now this may be UB, but it's such an integral feature for so many programs
			// that most if not all compilers support it, but I would like to avoid UB if possible.

			// NOTE: As far as the problems that would arise if one could reinterpret_cast
			// wildly from type to type, the above way of doing it isn't bad at all,
			// you just need to make sure not to use the previous pointer and the new pointer
			// in the same blocks of code, prefferrably never use the previous pointer again.
			// Then, the compiler can optimize everything so that there are no downsides.
			// NOTE: There aren't really any downsides anyway because we are just reading,
			// and we never write, so caching and ordering and such cannot cause us harm.

			// NOTE: There is a way to get around all this with memcpy or std::copy or something,
			// at least that's what I've heard, but I'm not willing to sacrifice performance
			// just because C++ is an unpolished mess of a language.

			// NOTE: Anyway, the above wouldn't work anyway since the types can be different
			// widths, but C++ still has a problem with handling type punning, so I'm leaving the
			// comments in to reference later if I need to.

			// NOTE: Luckily, since intptr_t is always an integer (I think) (or maybe sometimes
			// a pointer, which would also be ok for this) and cl_platform_id is always a pointer,
			// the normal conversion between the two is more than sufficient for this use-case.
			bestPlatform = (cl_platform_id)context_properties[i + 1];

			return CL_SUCCESS;
		}
	}

	// NOTE: Sort of suboptimal error code to return since other places can also cause it in
	// this function, but this instance should never really be thrown unless there is a bug
	// somewhere or the OpenCL implementation is buggy or something, so it's fine.
	// It's mainly just for me, the developer.
	return CL_EXT_NO_PLATFORMS_FOUND;
	*/

	// NOTE: The above code only returns the platform if you explicitly specified the platform in clCreateContext(),
	// which we did not and will not. Instead, let's do it like this:

	err = clGetDeviceInfo(bestDevice, CL_DEVICE_PLATFORM, sizeof(cl_platform_id), &bestDevice, nullptr);
	if (err != CL_SUCCESS) { return err; }

	return CL_SUCCESS;
}

char* readFromSourceFile(const char* sourceFile, cl_int& errorCode) {
	std::ifstream kernelSourceFile(sourceFile, std::ios::beg);
	if (!kernelSourceFile.is_open()) { errorCode = CL_EXT_FILE_OPEN_FAILED; return nullptr; }
#pragma push_macro(max)																																		// Count the characters inside the source file, construct large enough buffer, read from file into buffer.
#undef max																																					// The reason for this push, pop and undef stuff is because max is a macro defined in Windows.h header and it interferes with our code.
	kernelSourceFile.ignore(std::numeric_limits<std::streamsize>::max());																					// We shortly undefine it and then pop it's original definition back into the empty slot when we're done with our code.
#pragma pop_macro(max)
	std::streamsize kernelSourceSize = kernelSourceFile.gcount();
	char* kernelSource = new (std::nothrow) char[kernelSourceSize + 1];
	if (!kernelSource) { errorCode = CL_EXT_INSUFFICIENT_HOST_MEM; return nullptr; }
	kernelSourceFile.seekg(0, std::ios::beg);
	kernelSourceFile.read(kernelSource, kernelSourceSize);
	kernelSourceFile.close();
	kernelSource[kernelSourceSize] = '\0';
	errorCode = CL_SUCCESS;
	return kernelSource;																																	// Returning a raw heap-initialized char array is potentially dangerous. The caller must delete the array.
}

cl_int setupComputeKernelFromString(cl_context context, cl_device_id device, const char* sourceCodeString, const char* kernelName, cl_program& program, cl_kernel& kernel, size_t& kernelWorkGroupSize, std::string& buildLog) {
	cl_int err;
	program = clCreateProgramWithSource(context, 1, (const char* const*)&sourceCodeString, nullptr, &err);
	delete[] sourceCodeString;
	if (!program) { return CL_EXT_CREATE_PROGRAM_FAILED; }

	switch (clBuildProgram(program, 0, nullptr, nullptr, nullptr, nullptr)) {
	case CL_SUCCESS: break;
	case CL_BUILD_PROGRAM_FAILURE:
		{
			size_t buildLogSize;

			// IMPORTANT-SIDE-NOTE: The above initialization of buildLogSize is actually legal even without the extra scope with the { } symbols.
			// What isn't legal is size_t buildLogSize = something. Considering the goto-nature of the switch statement and the stacks involved, both shouldn't be allowed,
			// or so I thought. The language designers thought differently. Basically, when gotoing somewhere, the compiler makes sure whatever variables were declared
			// in the code you missed are pushed onto the stack. Why people thought to do it like this instead of just forcing you to explicitly put in a scope somewhere
			// to explicitly limit the variable's lifetime is beyond me at the moment.
			// Obviously, since the in between code wasn't executed, the values of the "extra" variables that were pushed are just uninitialized, so you probably shouldn't
			// read from them in the after-the-goto code, but you can write to them and use them, which surprised me, but makes sense given the behaviour that I just
			// talked about.
			// ANYWAY: The reason "int x; x = 1;" works and "int x = 1;" doesn't even though they are the same thing is because the compiler can't put an uninitialized thing on the stack if that thing uses some sort of special constructor. Now scalar types like int can never
			// use some special constructor, since they're primitive, but stuff like structs and such
			// can only work if you default initialize them and if the default constructor is trivial (I believe that essentially
			// means it doesn't really do anything to prevent uninitialization, something like that).
			// So that the default constructor is used when goto is hit and also when it is not hit, the code itself
			// must do "class instance;" instead of "class instance = ...;", since this is simpler than using special constructor
			// when goto is not hit and default constructor when goto is hit.
			// Like I said, all this doesn't really apply to scalar types, but I guess they work the same way for simplicity, thank god.
			// BOTTOM-LINE: All this is to enforce the fact that the compiler can trivially bump the stack when doing goto,
			// and forcing "class instance;" is simply to enforce the invokation of the default constructor whether goto is hit or not,
			// since that is simpler than the alternative.

			err = clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, 0, nullptr, &buildLogSize);
			if (err != CL_SUCCESS) { clReleaseProgram(program); return err; }
			char* buildLogBuffer = new (std::nothrow) char[buildLogSize];
			if (!buildLogBuffer) { clReleaseProgram(program); return CL_EXT_INSUFFICIENT_HOST_MEM; }
			err = clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, buildLogSize, buildLogBuffer, nullptr);
			if (err != CL_SUCCESS) {
				delete[] buildLogBuffer;
				clReleaseProgram(program);
				return CL_EXT_GET_BUILD_LOG_FAILED;
			}
			clReleaseProgram(program);
			buildLog = std::string(buildLogBuffer, buildLogSize - 1);																							// Give back to user as an std::string to avoid headaches with dangling pointers. WE DON'T DELETE buildLogBuffer here because it's now under the care of buildLog std::string.
			return CL_EXT_BUILD_FAILED_WITH_BUILD_LOG;
		}
	default:
		clReleaseProgram(program);
		return CL_EXT_BUILD_FAILED_WITHOUT_BUILD_LOG;
	}

	kernel = clCreateKernel(program, kernelName, &err);
	if (!kernel) { clReleaseProgram(program); return CL_EXT_CREATE_KERNEL_FAILED; }

	err = clGetKernelWorkGroupInfo(kernel, device, CL_KERNEL_WORK_GROUP_SIZE, sizeof(size_t), &kernelWorkGroupSize, nullptr);
	if (err != CL_SUCCESS) {
		clReleaseKernel(kernel);
		clReleaseProgram(program);
		return CL_EXT_GET_KERNEL_WORK_GROUP_INFO_FAILED;
	}

	size_t kernelPreferredWorkGroupSizeMultiple;																										// The kernels preferred work group size multiple, which should go evenly into whatever size we end up picking for the kernel work group.
	err = clGetKernelWorkGroupInfo(kernel, device, CL_KERNEL_PREFERRED_WORK_GROUP_SIZE_MULTIPLE, sizeof(size_t), &kernelPreferredWorkGroupSizeMultiple, nullptr);
	if (err != CL_SUCCESS) {
		clReleaseKernel(kernel);
		clReleaseProgram(program);
		return CL_EXT_GET_KERNEL_WORK_GROUP_INFO_FAILED;
	}

	// Compute optimal work group size for kernel based on the raw kernel maximum and kernel preferred work group size multiple.
	if (kernelWorkGroupSize > kernelPreferredWorkGroupSizeMultiple) { kernelWorkGroupSize -= kernelWorkGroupSize % kernelPreferredWorkGroupSizeMultiple; }

	return CL_SUCCESS;
}

cl_int setupComputeKernelFromFile(cl_context context, cl_device_id device, const char* sourceCodeFile, const char* kernelName, cl_program& program, cl_kernel& kernel, size_t& kernelWorkGroupSize, std::string& buildLog) {
	cl_int err;
	const char* sourceCodeString = readFromSourceFile(sourceCodeFile, err);
	if (!sourceCodeString) { return err; }
	return setupComputeKernelFromString(context, device, sourceCodeString, kernelName, program, kernel, kernelWorkGroupSize, buildLog);
}
