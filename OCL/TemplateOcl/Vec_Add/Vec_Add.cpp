// Vec_Add.cpp : This file contains the 'main' function. Program execution begins and ends there.
// 
// https://www.eriksmistad.no/getting-started-with-opencl-and-gpu-computing/
// https://github.com/smistad/OpenCL-Getting-Started/
// https://github.com/smistad/OpenCL-Getting-Started/
// cl_version.h: CL_TARGET_OPENCL_VERSION is not defined.Defaulting to 220 (OpenCL 2.2)
// M:\Prj_Cpp\OCL\TemplateOcl\Vec_Add\Vec_Add.cpp(32, 10) : error C4996 : 'fopen' : This function or variable may be unsafe.Consider using fopen_s instead.
// To disable deprecation, use _CRT_SECURE_NO_WARNINGS.See online help for details.
// M:\Prj_Cpp\OCL\TemplateOcl\Vec_Add\Vec_Add.cpp(54, 38) : error C4996 : 'clCreateCommandQueue' : was declared deprecated

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

#include <stdio.h>
#include <stdlib.h>

// supports OpenCL 1.2
#define CL_TARGET_OPENCL_VERSION 120
#include <CL/cl.h>

#define MAX_SOURCE_SIZE (0x100000)


int main()
{
    const char* pFilePath = "M:/Prj_Cpp/OCL/TemplateOcl/Vec_Add/vector_add_kernel.cl";

    //std::cout << "Hello World!\n";
    // Create the two input vectors
    int i;
    const int LIST_SIZE = 1024;
    int* A = (int*)malloc(sizeof(int) * LIST_SIZE);
    int* B = (int*)malloc(sizeof(int) * LIST_SIZE);
    for (i = 0; i < LIST_SIZE; i++) {
        A[i] = i;
        B[i] = LIST_SIZE - i;
    }

    // Load the kernel source code into the array source_str
    FILE* fp;
    char* source_str;
    size_t source_size;

    fp = fopen(pFilePath, "r");
    if (!fp) {
        fprintf(stderr, "Failed to load kernel.\n");
        exit(1);
    }
    source_str = (char*)malloc(MAX_SOURCE_SIZE);
    source_size = fread(source_str, 1, MAX_SOURCE_SIZE, fp);
    fclose(fp);

    // Get platform and device information
    cl_platform_id platform_id = NULL;
    cl_device_id device_id = NULL;
    cl_uint ret_num_devices;
    cl_uint ret_num_platforms;
    cl_int ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
    ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_DEFAULT, 1,
        &device_id, &ret_num_devices);

    // Create an OpenCL context
    cl_context context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret);

    // Create a command queue
    cl_command_queue command_queue = clCreateCommandQueue(context, device_id, 0, &ret);

    // Create memory buffers on the device for each vector 
    cl_mem a_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY,
        LIST_SIZE * sizeof(int), NULL, &ret);
    cl_mem b_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY,
        LIST_SIZE * sizeof(int), NULL, &ret);
    cl_mem c_mem_obj = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
        LIST_SIZE * sizeof(int), NULL, &ret);

    // Copy the lists A and B to their respective memory buffers
    ret = clEnqueueWriteBuffer(command_queue, a_mem_obj, CL_TRUE, 0,
        LIST_SIZE * sizeof(int), A, 0, NULL, NULL);
    ret = clEnqueueWriteBuffer(command_queue, b_mem_obj, CL_TRUE, 0,
        LIST_SIZE * sizeof(int), B, 0, NULL, NULL);

    // Create a program from the kernel source
    cl_program program = clCreateProgramWithSource(context, 1,
        (const char**)&source_str, (const size_t*)&source_size, &ret);

    // Build the program
    ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);

    // Create the OpenCL kernel
    cl_kernel kernel = clCreateKernel(program, "vector_add", &ret);

    // Set the arguments of the kernel
    ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void*)&a_mem_obj);
    ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void*)&b_mem_obj);
    ret = clSetKernelArg(kernel, 2, sizeof(cl_mem), (void*)&c_mem_obj);

    // Execute the OpenCL kernel on the list
    size_t global_item_size = LIST_SIZE; // Process the entire lists
    size_t local_item_size = 64; // Divide work items into groups of 64
    ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL,
        &global_item_size, &local_item_size, 0, NULL, NULL);

    // Read the memory buffer C on the device to the local variable C
    int* C = (int*)malloc(sizeof(int) * LIST_SIZE);
    ret = clEnqueueReadBuffer(command_queue, c_mem_obj, CL_TRUE, 0,
        LIST_SIZE * sizeof(int), C, 0, NULL, NULL);

    // Display the result to the screen
    for (i = 0; i < LIST_SIZE; i++)
        printf("%d + %d = %d\n", A[i], B[i], C[i]);

    // Clean up
    ret = clFlush(command_queue);
    ret = clFinish(command_queue);
    ret = clReleaseKernel(kernel);
    ret = clReleaseProgram(program);
    ret = clReleaseMemObject(a_mem_obj);
    ret = clReleaseMemObject(b_mem_obj);
    ret = clReleaseMemObject(c_mem_obj);
    ret = clReleaseCommandQueue(command_queue);
    ret = clReleaseContext(context);
    free(A);
    free(B);
    free(C);

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
