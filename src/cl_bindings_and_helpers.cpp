#include "cl_bindings_and_helpers.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <cstdint>						// For fixed-width types.

#include <new>							// For std::nothrow.

#include <fstream>						// For reading OpenCL source code from file.

#include <string>						// For std::string.

#include <limits>						// for std::numeric_limits

#include <vector>

HMODULE DLLHandle;

bool loadOpenCLLib() noexcept { return DLLHandle = LoadLibraryA("OpenCL.dll"); }

bool bind_clGetPlatformIDs() noexcept { return clGetPlatformIDs = (clGetPlatformIDs_func)GetProcAddress(DLLHandle, "clGetPlatformIDs"); }
bool bind_clGetPlatformInfo() noexcept { return clGetPlatformInfo = (clGetPlatformInfo_func)GetProcAddress(DLLHandle, "clGetPlatformInfo"); }
bool bind_clGetDeviceIDs() noexcept { return clGetDeviceIDs = (clGetDeviceIDs_func)GetProcAddress(DLLHandle, "clGetDeviceIDs"); }
bool bind_clGetDeviceInfo() noexcept { return clGetDeviceInfo = (clGetDeviceInfo_func)GetProcAddress(DLLHandle, "clGetDeviceInfo"); }
bool bind_clCreateContext() noexcept { return clCreateContext = (clCreateContext_func)GetProcAddress(DLLHandle, "clCreateContext"); }
bool bind_clGetContextInfo() noexcept { return clGetContextInfo = (clGetContextInfo_func)GetProcAddress(DLLHandle, "clGetContextInfo"); }
bool bind_clCreateCommandQueue() noexcept { return clCreateCommandQueue = (clCreateCommandQueue_func)GetProcAddress(DLLHandle, "clCreateCommandQueue"); }
bool bind_clCreateProgramWithSource() noexcept { return clCreateProgramWithSource = (clCreateProgramWithSource_func)GetProcAddress(DLLHandle, "clCreateProgramWithSource"); }
bool bind_clBuildProgram() noexcept { return clBuildProgram = (clBuildProgram_func)GetProcAddress(DLLHandle, "clBuildProgram"); }
bool bind_clGetProgramBuildInfo() noexcept { return clGetProgramBuildInfo = (clGetProgramBuildInfo_func)GetProcAddress(DLLHandle, "clGetProgramBuildInfo"); }
bool bind_clCreateKernel() noexcept { return clCreateKernel = (clCreateKernel_func)GetProcAddress(DLLHandle, "clCreateKernel"); }
bool bind_clCreateBuffer() noexcept { return clCreateBuffer = (clCreateBuffer_func)GetProcAddress(DLLHandle, "clCreateBuffer"); }
bool bind_clCreateImage2D() noexcept { return clCreateImage2D = (clCreateImage2D_func)GetProcAddress(DLLHandle, "clCreateImage2D"); }
bool bind_clSetKernelArg() noexcept { return clSetKernelArg = (clSetKernelArg_func)GetProcAddress(DLLHandle, "clSetKernelArg"); }
bool bind_clGetKernelWorkGroupInfo() noexcept { return clGetKernelWorkGroupInfo = (clGetKernelWorkGroupInfo_func)GetProcAddress(DLLHandle, "clGetKernelWorkGroupInfo"); }
bool bind_clEnqueueNDRangeKernel() noexcept { return clEnqueueNDRangeKernel = (clEnqueueNDRangeKernel_func)GetProcAddress(DLLHandle, "clEnqueueNDRangeKernel"); }
bool bind_clFlush() noexcept { return clFlush = (clFlush_func)GetProcAddress(DLLHandle, "clFlush"); }
bool bind_clFinish() noexcept { return clFinish = (clFinish_func)GetProcAddress(DLLHandle, "clFinish"); }
bool bind_clEnqueueWriteBuffer() noexcept { return clEnqueueWriteBuffer = (clEnqueueWriteBuffer_func)GetProcAddress(DLLHandle, "clEnqueueWriteBuffer"); }
bool bind_clEnqueueReadBuffer() noexcept { return clEnqueueReadBuffer = (clEnqueueReadBuffer_func)GetProcAddress(DLLHandle, "clEnqueueReadBuffer"); }
bool bind_clEnqueueWriteImage() noexcept { return clEnqueueWriteImage = (clEnqueueWriteImage_func)GetProcAddress(DLLHandle, "clEnqueueWriteImage"); }
bool bind_clEnqueueReadImage() noexcept { return clEnqueueReadImage = (clEnqueueReadImage_func)GetProcAddress(DLLHandle, "clEnqueueReadImage"); }
bool bind_clReleaseMemObject() noexcept { return clReleaseMemObject = (clReleaseMemObject_func)GetProcAddress(DLLHandle, "clReleaseMemObject"); }
bool bind_clReleaseKernel() noexcept { return clReleaseKernel = (clReleaseKernel_func)GetProcAddress(DLLHandle, "clReleaseKernel"); }
bool bind_clReleaseProgram() noexcept { return clReleaseProgram = (clReleaseProgram_func)GetProcAddress(DLLHandle, "clReleaseProgram"); }
bool bind_clReleaseCommandQueue() noexcept { return clReleaseCommandQueue = (clReleaseCommandQueue_func)GetProcAddress(DLLHandle, "clReleaseCommandQueue"); }
bool bind_clReleaseContext() noexcept { return clReleaseContext = (clReleaseContext_func)GetProcAddress(DLLHandle, "clReleaseContext"); }

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

constexpr bool is_character_whitespace(char character) noexcept {
	switch (character) {
	case ' ': return true;
	case '\t': return true;
	default: return false;
	}
}

// NOTE: Does what the name implies, while trying to be able to parse as many different variations of the version string syntax,
// for future-proofness.
VersionIdentifier convertOpenCLVersionStringToVersionIdentifier(const char* string) noexcept {
	// NOTE: In this function, we encode the parsing algorithm into the control flow. This is an acceptable approach,
	// but technically a custom DFA simulator and table would be more efficient at this problem (because their translation to assembly
	// results in faster instructions than the translation of the control flow version (and this isn't something that we can
	// properly rely on the optimizer for either, at least as far as I can tell)). I'm not going to get into it in depth here,
	// but it's got to do with the fact that the DFA heavily relies on memory caching, with minimal branch predictor overhead, where-as
	// the control flow version heavily relies on caching as well, but has pretty substantial branch predictor overhead.
	// This only makes a difference when nesting switch statements, which is nice, but as it happens, we are nesting them here.
	// That's why my point about DFA's being better here stands.
	// BUT: I'm keeping the control flow version, because it's easier to understand and expand upon, and this part of the code doesn't have to
	// be as fast as possible anyway, although I'm still going to try to make it as fast as possible within the bounds of the control flow system.

	const unsigned char *string_ptr = (const unsigned char *)string;		// TO AVOID SIGNED OVERFLOW!

	uint32_t major;
	uint32_t minor;

skip_past_junk:
	// Skip past all the junk that comes before the version number.
	while (true) {
		// NOTE: Can't be a uint8_t because unsigned char might be bigger than a byte and that would overflow, which would make digit <= 9 false-trigger.
		const unsigned char digit = *string_ptr - '0';	// NOTE: This isn't UB, I assure you, it is defined and produces the correct behavior.
		if (digit <= 9) { major = digit; string_ptr++; break; }
		if (*string_ptr == '\0') { return { 0, 0 }; }
		// QUESTION: Why narrowing conversions disallowed in aggregate initialization?
		// ANSWER: Because implicit narrowing conversions should be disallowed everywhere, they are the cause of many bugs, or so I've heard.
		// QUESTION: Then why are they allowed in most places?
		// ANSWER: Because C++ is not a great language, only a good language. More concretely, because C did it like this and C++ decided they should stick with the program.
		// IMPORTANT: Allowing implicit narrowing conversions is nothing but a terrible idea though, that much is clear.
		// NOTE: You should always explicitly narrowly convert instead of implicitly, to signal the intent to the reader thuroughly.
		string_ptr++;
		// TODO: Re-research about branches and which configurations have which overhead and how the branch predictor behaves specifically for x86.
		// Once you've done that, provide reasoning for your choices in this function regarding if order and placement and such.
		// I've already got a vague idea of what's efficient, so these orderings are probably pretty good, but I should re-research it as I said.
	}

	// Parse the major version number.
	while (true) {
		const unsigned char digit = *string_ptr - '0';
		if (digit > 9) { break; }		// NOTE: This is on purpose, it isn't an error, even though the simplicity is suspect.
		major = major * 10 + digit;
		if (major > (uint16_t)-1) {
			// NOTE: This section skips past digits until it reaches anything that's not a digit. Then it starts from junk skipping again.
			string_ptr++;
			while (true) {
				// NOTE: I think consolidating the following into a switch statement might actually be less efficient because of branch prediction.
				// If not, the compiler will probably optimize into a switch statement anyway, but I think it might actually stay like it is,
				// because it seems more efficient. TODO: Take a look at the assembly and test your theory.
				if (*string_ptr - '0' <= 9) { string_ptr++; continue; }
				if (*string_ptr == '\0') { return { 0, 0 }; }
				goto skip_past_junk;
			}
		}
		string_ptr++;
	}

	// Wait for one dot to pass, all the while filtering out whitespace. If invalid character is encountered, go back to junk skipping.
	while (true) {
		if (*string_ptr != '.') {
			if (!is_character_whitespace(*string_ptr)) {
				if (*string_ptr == '\0') { return { 0, 0 }; }
				goto skip_past_junk;			// NOTE: Not incrementing string_ptr on purpose here, very useful.
			}
			// NOTE: This case is the jumpless case because it's the most probable.
			string_ptr++;
			continue;
		}
		string_ptr++;
		goto break_out_of_loop;
	}
break_out_of_loop:

	// Wait for minor version number, only filtering out whitespace. If invalid character is encountered, go back to junk skipping.
	while (true) {
		const unsigned char digit = *string_ptr - '0';		// NOTE: Optimizer will very probably optimize this var out and work on minor directly.
		if (digit > 9) {
			if (!is_character_whitespace(*string_ptr)) {
				if (*string_ptr == '\0') { return { 0, 0 }; }
				goto skip_past_junk;
			}
			// NOTE: This case is the jumpless case because it's the most probable.
			// TODO: Again, check through x86 jump optimization possibilites online.
			string_ptr++;
			continue;
		}
		minor = digit;
		string_ptr++;
		break;
	}

	// Parse the minor version number. If anything but a number gets in the way, we're done.
	for (; *string_ptr != '\0'; string_ptr++) {
		const unsigned char digit = *string_ptr - '0';
		if (digit > 9) { return { (uint16_t)major, (uint16_t)minor }; }
		minor = minor * 10 + digit;
		if (minor > (uint16_t)-1) { return { 0, 0 }; }
		continue;
	}

	// End of string, return result.
	return { (uint16_t)major, (uint16_t)minor };
}

OpenCLDeviceCollection getAllOpenCLDevices(cl_int& err, const VersionIdentifier& minimumPlatformVersion) noexcept {
	cl_uint platformCount;
	err = clGetPlatformIDs(0, nullptr, &platformCount);
	if (err != CL_SUCCESS) { return OpenCLDeviceCollection(); }
	if (!platformCount) { return OpenCLDeviceCollection(); }

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

	// NOTE: I don't know if these heap allocations are worse than avoiding vectors by sorting through platform versions once for counting
	// and then once again for filling (see the way you've been doing it for compile-time algorithms for more clarity).
	// The second option would make the code more complex, which isn't worth the potential performance boost because this code doesn't need to be fast
	// at all.
	// We could also make a custom vector that stack allocates for small amounts and then switches to heap for bigger amounts,
	// but that complexity also isn't worth it.
	// IN CONCLUSION: I'm keeping it like this because the code complexity is the simplest.
	// NOTE: If you're wondering why we don't use vectors for everything in this function, see below.
	std::vector<cl_uint> validPlatforms;
	std::vector<cl_uint> validPlatformDeviceCounts;
	size_t totalDeviceCount = 0;

	for (size_t i = 0; i < platformCount; i++) {
		const cl_platform_id& currentPlatform = platforms[i];	// NOTE: You might think you can just as well leave out the reference, but I think it is probably better with the reference since there are ways a copy can be avoided (stays in same register the whole time for example) and we don't want to hinder that.
																// NOTE: Although on second thought, this technique doesn't really do anything in this case since the compiler can easily optimize it even if we just use a copy.
																// NOTE: But it's still good practice because it expresses your thoughts more clearly and I guess is better for some optimizations, so we're doing it.
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
			validPlatforms.push_back(i);

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

			validPlatformDeviceCounts.push_back(deviceCount);
			totalDeviceCount += deviceCount;

			continue;
		}
	}

	/*
	* 
	* NOTE: We go through everything, get the counts, then construct the OpenCLDeviceCollection, go through everything again
	* and get the data. The reason we do this is because std::vector isn't able to lose control of it's data.
	* We could create our own std::vector (would be easy in this case since we barely use any of the functionality) and add
	* the functionality that we want, but this is easier and simpler. Honestly, not using vectors for most of the stuff might even be
	* faster because we avoid heap allocations, but I don't know.
	* The important thing is that this version makes the code less complex (because no vector implementation), which is worth the possible performance loss
	* because this code isn't performance critical at all.
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

	// TODO: Fix visual studio formatting so that it doesn't put asterisk on the type and lets me align it to the var name in for loops and such.
}

cl_int initOpenCLVarsForBestDevice(const VersionIdentifier& minimumTargetPlatformVersion, cl_platform_id& bestPlatform, cl_device_id& bestDevice, cl_context& context, cl_command_queue& commandQueue) noexcept {
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

	err = clGetDeviceInfo(bestDevice, CL_DEVICE_PLATFORM, sizeof(cl_platform_id), &bestPlatform, nullptr);
	if (err != CL_SUCCESS) { return err; }

	return CL_SUCCESS;

	// NOTE: The rest of this function is just an old implementation that I'm keeping around for reference.

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
}

char* readFromSourceFile(const char* sourceFile, cl_int& errorCode) noexcept {
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

cl_int setupComputeKernelFromString(cl_context context, cl_device_id device, const char* sourceCodeString, const char* kernelName, cl_program& program, cl_kernel& kernel, size_t& kernelWorkGroupSize, std::string& buildLog) noexcept {
	cl_int err;
	program = clCreateProgramWithSource(context, 1, (const char* const*)&sourceCodeString, nullptr, &err);
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

cl_int setupComputeKernelFromFile(cl_context context, cl_device_id device, const char* sourceCodeFile, const char* kernelName, cl_program& program, cl_kernel& kernel, size_t& kernelWorkGroupSize, std::string& buildLog) noexcept {
	cl_int err;
	const char* sourceCodeString = readFromSourceFile(sourceCodeFile, err);
	if (!sourceCodeString) { return err; }
	err = setupComputeKernelFromString(context, device, sourceCodeString, kernelName, program, kernel, kernelWorkGroupSize, buildLog);
	delete[] sourceCodeString;
	return err;
}
