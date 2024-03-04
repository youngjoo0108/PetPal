

/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from ObjectInfo_.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Connext distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Connext manual.
*/

#ifndef ObjectInfo__57146963_h
#define ObjectInfo__57146963_h

#ifndef NDDS_STANDALONE_TYPE
#ifndef ndds_cpp_h
#include "ndds/ndds_cpp.h"
#endif
#else
#include "ndds_standalone_type.h"
#endif

namespace ssafy_msgs {
    namespace msg {
        namespace dds_ {

            extern const char *ObjectInfo_TYPENAME;

            struct ObjectInfo_Seq;
            #ifndef NDDS_STANDALONE_TYPE
            class ObjectInfo_TypeSupport;
            class ObjectInfo_DataWriter;
            class ObjectInfo_DataReader;
            #endif

            class ObjectInfo_ 
            {
              public:
                typedef struct ObjectInfo_Seq Seq;
                #ifndef NDDS_STANDALONE_TYPE
                typedef ObjectInfo_TypeSupport TypeSupport;
                typedef ObjectInfo_DataWriter DataWriter;
                typedef ObjectInfo_DataReader DataReader;
                #endif

                DDS_Short   num_obj_ ;
                DDS_ShortSeq  idx_obj_ ;
                DDS_FloatSeq  x_ ;
                DDS_FloatSeq  y_ ;

            };
            #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT_ssafy_msgs)
            /* If the code is building on Windows, start exporting symbols.
            */
            #undef NDDSUSERDllExport
            #define NDDSUSERDllExport __declspec(dllexport)
            #endif

            NDDSUSERDllExport DDS_TypeCode* ObjectInfo__get_typecode(void); /* Type code */

            DDS_SEQUENCE(ObjectInfo_Seq, ObjectInfo_);

            NDDSUSERDllExport
            RTIBool ObjectInfo__initialize(
                ObjectInfo_* self);

            NDDSUSERDllExport
            RTIBool ObjectInfo__initialize_ex(
                ObjectInfo_* self,RTIBool allocatePointers,RTIBool allocateMemory);

            NDDSUSERDllExport
            RTIBool ObjectInfo__initialize_w_params(
                ObjectInfo_* self,
                const struct DDS_TypeAllocationParams_t * allocParams);  

            NDDSUSERDllExport
            void ObjectInfo__finalize(
                ObjectInfo_* self);

            NDDSUSERDllExport
            void ObjectInfo__finalize_ex(
                ObjectInfo_* self,RTIBool deletePointers);

            NDDSUSERDllExport
            void ObjectInfo__finalize_w_params(
                ObjectInfo_* self,
                const struct DDS_TypeDeallocationParams_t * deallocParams);

            NDDSUSERDllExport
            void ObjectInfo__finalize_optional_members(
                ObjectInfo_* self, RTIBool deletePointers);  

            NDDSUSERDllExport
            RTIBool ObjectInfo__copy(
                ObjectInfo_* dst,
                const ObjectInfo_* src);

            #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT_ssafy_msgs)
            /* If the code is building on Windows, stop exporting symbols.
            */
            #undef NDDSUSERDllExport
            #define NDDSUSERDllExport
            #endif
        } /* namespace dds_  */
    } /* namespace msg  */
} /* namespace ssafy_msgs  */

#endif /* ObjectInfo_ */

