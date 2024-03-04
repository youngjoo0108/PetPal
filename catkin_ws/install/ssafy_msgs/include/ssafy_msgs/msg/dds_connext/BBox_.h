

/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from BBox_.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Connext distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Connext manual.
*/

#ifndef BBox__1013145143_h
#define BBox__1013145143_h

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

            extern const char *BBox_TYPENAME;

            struct BBox_Seq;
            #ifndef NDDS_STANDALONE_TYPE
            class BBox_TypeSupport;
            class BBox_DataWriter;
            class BBox_DataReader;
            #endif

            class BBox_ 
            {
              public:
                typedef struct BBox_Seq Seq;
                #ifndef NDDS_STANDALONE_TYPE
                typedef BBox_TypeSupport TypeSupport;
                typedef BBox_DataWriter DataWriter;
                typedef BBox_DataReader DataReader;
                #endif

                DDS_Short   num_bbox_ ;
                DDS_ShortSeq  idx_bbox_ ;
                DDS_ShortSeq  x_ ;
                DDS_ShortSeq  y_ ;
                DDS_ShortSeq  w_ ;
                DDS_ShortSeq  h_ ;

            };
            #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT_ssafy_msgs)
            /* If the code is building on Windows, start exporting symbols.
            */
            #undef NDDSUSERDllExport
            #define NDDSUSERDllExport __declspec(dllexport)
            #endif

            NDDSUSERDllExport DDS_TypeCode* BBox__get_typecode(void); /* Type code */

            DDS_SEQUENCE(BBox_Seq, BBox_);

            NDDSUSERDllExport
            RTIBool BBox__initialize(
                BBox_* self);

            NDDSUSERDllExport
            RTIBool BBox__initialize_ex(
                BBox_* self,RTIBool allocatePointers,RTIBool allocateMemory);

            NDDSUSERDllExport
            RTIBool BBox__initialize_w_params(
                BBox_* self,
                const struct DDS_TypeAllocationParams_t * allocParams);  

            NDDSUSERDllExport
            void BBox__finalize(
                BBox_* self);

            NDDSUSERDllExport
            void BBox__finalize_ex(
                BBox_* self,RTIBool deletePointers);

            NDDSUSERDllExport
            void BBox__finalize_w_params(
                BBox_* self,
                const struct DDS_TypeDeallocationParams_t * deallocParams);

            NDDSUSERDllExport
            void BBox__finalize_optional_members(
                BBox_* self, RTIBool deletePointers);  

            NDDSUSERDllExport
            RTIBool BBox__copy(
                BBox_* dst,
                const BBox_* src);

            #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT_ssafy_msgs)
            /* If the code is building on Windows, stop exporting symbols.
            */
            #undef NDDSUSERDllExport
            #define NDDSUSERDllExport
            #endif
        } /* namespace dds_  */
    } /* namespace msg  */
} /* namespace ssafy_msgs  */

#endif /* BBox_ */

