#include "cl_bindings_and_helpers.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <cstdint>						// For fixed-width types.

#include <new>							// For std::nothrow.

#include <fstream>						// For reading OpenCL source code from file.

#include <string>						// For std::string.

VersionIdentifier::VersionIdentifier(uint16_t major, uint16_t minor) : major(major), minor(minor) { }

bool VersionIdentifier::operator>=(const VersionIdentifier& rightSide) {
	if (major > rightSide.major) { return true; }
	if (minor > rightSide.minor) { return true; }
}

HMODULE DLLHandle;

bool loadOpenCLLib() { return DLLHandle = LoadLibraryA("OpenCL.dll"); }

bool bind_clGetPlatformIDs() { return clGetPlatformIDs = (clGetPlatformIDs_func)GetProcAddress(DLLHandle, "clGetPlatformIDs"); }
bool bind_clGetPlatformInfo() { return clGetPlatformInfo = (clGetPlatformInfo_func)GetProcAddress(DLLHandle, "clGetPlatformInfo"); }
bool bind_clGetDeviceIDs() { return clGetDeviceIDs = (clGetDeviceIDs_func)GetProcAddress(DLLHandle, "clGetDeviceIDs"); }
bool bind_clGetDeviceInfo() { return clGetDeviceInfo = (clGetDeviceInfo_func)GetProcAddress(DLLHandle, "clGetDeviceInfo"); }
bool bind_clCreateContext() { return clCreateContext = (clCreateContext_func)GetProcAddress(DLLHandle, "clCreateContext"); }
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

#define CHECK_FUNC_VALIDITY(func) if (!(func)) { FreeLibrary(DLLHandle); return CL_EXT_INIT_FAILURE; }

cl_int initOpenCLBindings() {
	if (!LoadOpenCLLib) { return CL_EXT_INIT_FAILURE; }

	CHECK_FUNC_VALIDITY(bind_clGetPlatformIDs());										// Go through all the functions and bind them one by one.
	CHECK_FUNC_VALIDITY(bind_clGetPlatformInfo());										// As soon as a bind fails, try to free the library and subsequently return failure for the whole init function.
	CHECK_FUNC_VALIDITY(bind_clGetDeviceIDs());
	CHECK_FUNC_VALIDITY(bind_clGetDeviceInfo());
	CHECK_FUNC_VALIDITY(clCreateContext());
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

bool freeOpenCLLib() { return FreeLibrary(DLLHandle); }

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
		if (string[i] == '\0') { return VersionIdentifier(-1, -1); }
	}
}

cl_int initOpenCLVarsForBestDevice(const VersionIdentifier& minimumTargetPlatformVersion, cl_platform_id& bestPlatform, cl_device_id& bestDevice, cl_context& context, cl_command_queue& commandQueue) {
	cl_uint platformCount;
	cl_int err = clGetPlatformIDs(0, nullptr, &platformCount);
	if (err != CL_SUCCESS) { return err; }
	if (!platformCount) { return CL_EXT_NO_PLATFORMS_FOUND; }

	cl_platform_id* platforms = new (std::nothrow) cl_platform_id[platformCount];
	if (!platforms) { return CL_EXT_INSUFFICIENT_HOST_MEM; }
	err = clGetPlatformIDs(platformCount, platforms, nullptr);
	if (err != CL_SUCCESS) { delete[] platforms; return err; }

	size_t bestDeviceMaxWorkGroupSize = 0;
	for (int i = 0; i < platformCount; i++) {
		cl_platform_id& currentPlatform = platforms[i];												// NOTE: You might think you can just as well leave out the reference, but I think it is probably better with the reference since there are ways a copy can be avoided (stays in register the whole time for example) and we don't want to hinder that.

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
			err = clGetDeviceIDs(currentPlatform, CL_DEVICE_TYPE_GPU, 0, nullptr, &deviceCount);
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

cl_int setupComputeKernel(cl_context context, cl_device_id device, const char* sourceFile, const char* kernelName, cl_program& program, cl_kernel& kernel, size_t& kernelWorkGroupSize, std::string& buildLog) {
	cl_int err;
	const char* kernelSource = readFromSourceFile(sourceFile, err);
	if (!kernelSource) { return err; }
	program = clCreateProgramWithSource(context, 1, (const char* const*)&kernelSource, nullptr, &err);
	delete[] kernelSource;
	if (!program) { return err; }

	err = clBuildProgram(program, 0, nullptr, nullptr, nullptr, nullptr);
	if (err != CL_SUCCESS) {																																// If build fails, try to return the build log to the user.
		size_t buildLogSize;
		err = clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, 0, nullptr, &buildLogSize);
		if (err != CL_SUCCESS) { clReleaseProgram(program); return err; }
		char* buildLogBuffer = new (std::nothrow) char[buildLogSize];
		if (!buildLogBuffer) { clReleaseProgram(program); return CL_EXT_INSUFFICIENT_HOST_MEM; }
		err = clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, buildLogSize, buildLogBuffer, nullptr);
		if (err != CL_SUCCESS) {
			delete[] buildLogBuffer;
			clReleaseProgram(program);
			return err;
		}
		clReleaseProgram(program);
		buildLog = std::string(buildLogBuffer, buildLogSize - 1);																							// Give back to user as an std::string to avoid headaches with dangling pointers. WE DON'T DELETE buildLogBuffer here because it's now under the care of buildLog std::string.
		return CL_EXT_BUILD_FAILED_WITH_BUILD_LOG;
	}

	kernel = clCreateKernel(program, kernelName, &err);
	if (!kernel) { clReleaseProgram(program); return err; }

	err = clGetKernelWorkGroupInfo(kernel, device, CL_KERNEL_WORK_GROUP_SIZE, sizeof(size_t), &kernelWorkGroupSize, nullptr);
	if (err != CL_SUCCESS) {
		clReleaseKernel(kernel);
		clReleaseProgram(program);
		return err;
	}

	size_t kernelPreferredWorkGroupSizeMultiple;																										// The kernels preferred work group size multiple, which should go evenly into whatever size we end up picking for the kernel work group.
	err = clGetKernelWorkGroupInfo(kernel, device, CL_KERNEL_PREFERRED_WORK_GROUP_SIZE_MULTIPLE, sizeof(size_t), &kernelPreferredWorkGroupSizeMultiple, nullptr);
	if (err != CL_SUCCESS) {
		clReleaseKernel(kernel);
		clReleaseProgram(program);
		return err;
	}

	// Compute optimal work group size for kernel based on the raw kernel maximum and kernel preferred work group size multiple.
	if (kernelWorkGroupSize > kernelPreferredWorkGroupSizeMultiple) { kernelWorkGroupSize -= kernelWorkGroupSize % kernelPreferredWorkGroupSizeMultiple; }

	return CL_SUCCESS;
}
