#include "H264NALListModel.h"
#include <QFile>
#include <QColor>
#include <QDebug>

void print_bytes(char *buffer, uint8_t* buf, int len);
void print_slice_header(char *buffer, slice_header_t* sh);

/***************************** debug ******************************/

void print_sps(char *buffer, sps_t* sps)
{
    sprintf(buffer, "======= SPS =======\n");
    sprintf(buffer, " profile_idc : %d \n", sps->profile_idc );
    sprintf(buffer, " constraint_set0_flag : %d \n", sps->constraint_set0_flag );
    sprintf(buffer, " constraint_set1_flag : %d \n", sps->constraint_set1_flag );
    sprintf(buffer, " constraint_set2_flag : %d \n", sps->constraint_set2_flag );
    sprintf(buffer, " constraint_set3_flag : %d \n", sps->constraint_set3_flag );
    sprintf(buffer, " constraint_set4_flag : %d \n", sps->constraint_set4_flag );
    sprintf(buffer, " constraint_set5_flag : %d \n", sps->constraint_set5_flag );
    sprintf(buffer, " reserved_zero_2bits : %d \n", sps->reserved_zero_2bits );
    sprintf(buffer, " level_idc : %d \n", sps->level_idc );
    sprintf(buffer, " seq_parameter_set_id : %d \n", sps->seq_parameter_set_id );
    sprintf(buffer, " chroma_format_idc : %d \n", sps->chroma_format_idc );
    sprintf(buffer, " residual_colour_transform_flag : %d \n", sps->residual_colour_transform_flag );
    sprintf(buffer, " bit_depth_luma_minus8 : %d \n", sps->bit_depth_luma_minus8 );
    sprintf(buffer, " bit_depth_chroma_minus8 : %d \n", sps->bit_depth_chroma_minus8 );
    sprintf(buffer, " qpprime_y_zero_transform_bypass_flag : %d \n", sps->qpprime_y_zero_transform_bypass_flag );
    sprintf(buffer, " seq_scaling_matrix_present_flag : %d \n", sps->seq_scaling_matrix_present_flag );
    //  int seq_scaling_list_present_flag[8];
    //  void* ScalingList4x4[6];
    //  int UseDefaultScalingMatrix4x4Flag[6];
    //  void* ScalingList8x8[2];
    //  int UseDefaultScalingMatrix8x8Flag[2];
    sprintf(buffer, " log2_max_frame_num_minus4 : %d \n", sps->log2_max_frame_num_minus4 );
    sprintf(buffer, " pic_order_cnt_type : %d \n", sps->pic_order_cnt_type );
      sprintf(buffer, "   log2_max_pic_order_cnt_lsb_minus4 : %d \n", sps->log2_max_pic_order_cnt_lsb_minus4 );
      sprintf(buffer, "   delta_pic_order_always_zero_flag : %d \n", sps->delta_pic_order_always_zero_flag );
      sprintf(buffer, "   offset_for_non_ref_pic : %d \n", sps->offset_for_non_ref_pic );
      sprintf(buffer, "   offset_for_top_to_bottom_field : %d \n", sps->offset_for_top_to_bottom_field );
      sprintf(buffer, "   num_ref_frames_in_pic_order_cnt_cycle : %d \n", sps->num_ref_frames_in_pic_order_cnt_cycle );
    //  int offset_for_ref_frame[256];
    sprintf(buffer, " num_ref_frames : %d \n", sps->num_ref_frames );
    sprintf(buffer, " gaps_in_frame_num_value_allowed_flag : %d \n", sps->gaps_in_frame_num_value_allowed_flag );
    sprintf(buffer, " pic_width_in_mbs_minus1 : %d \n", sps->pic_width_in_mbs_minus1 );
    sprintf(buffer, " pic_height_in_map_units_minus1 : %d \n", sps->pic_height_in_map_units_minus1 );
    sprintf(buffer, " frame_mbs_only_flag : %d \n", sps->frame_mbs_only_flag );
    sprintf(buffer, " mb_adaptive_frame_field_flag : %d \n", sps->mb_adaptive_frame_field_flag );
    sprintf(buffer, " direct_8x8_inference_flag : %d \n", sps->direct_8x8_inference_flag );
    sprintf(buffer, " frame_cropping_flag : %d \n", sps->frame_cropping_flag );
      sprintf(buffer, "   frame_crop_left_offset : %d \n", sps->frame_crop_left_offset );
      sprintf(buffer, "   frame_crop_right_offset : %d \n", sps->frame_crop_right_offset );
      sprintf(buffer, "   frame_crop_top_offset : %d \n", sps->frame_crop_top_offset );
      sprintf(buffer, "   frame_crop_bottom_offset : %d \n", sps->frame_crop_bottom_offset );
    sprintf(buffer, " vui_parameters_present_flag : %d \n", sps->vui_parameters_present_flag );

    sprintf(buffer, "=== VUI ===\n");
    sprintf(buffer, " aspect_ratio_info_present_flag : %d \n", sps->vui.aspect_ratio_info_present_flag );
      sprintf(buffer, "   aspect_ratio_idc : %d \n", sps->vui.aspect_ratio_idc );
        sprintf(buffer, "     sar_width : %d \n", sps->vui.sar_width );
        sprintf(buffer, "     sar_height : %d \n", sps->vui.sar_height );
    sprintf(buffer, " overscan_info_present_flag : %d \n", sps->vui.overscan_info_present_flag );
      sprintf(buffer, "   overscan_appropriate_flag : %d \n", sps->vui.overscan_appropriate_flag );
    sprintf(buffer, " video_signal_type_present_flag : %d \n", sps->vui.video_signal_type_present_flag );
      sprintf(buffer, "   video_format : %d \n", sps->vui.video_format );
      sprintf(buffer, "   video_full_range_flag : %d \n", sps->vui.video_full_range_flag );
      sprintf(buffer, "   colour_description_present_flag : %d \n", sps->vui.colour_description_present_flag );
        sprintf(buffer, "     colour_primaries : %d \n", sps->vui.colour_primaries );
        sprintf(buffer, "   transfer_characteristics : %d \n", sps->vui.transfer_characteristics );
        sprintf(buffer, "   matrix_coefficients : %d \n", sps->vui.matrix_coefficients );
    sprintf(buffer, " chroma_loc_info_present_flag : %d \n", sps->vui.chroma_loc_info_present_flag );
      sprintf(buffer, "   chroma_sample_loc_type_top_field : %d \n", sps->vui.chroma_sample_loc_type_top_field );
      sprintf(buffer, "   chroma_sample_loc_type_bottom_field : %d \n", sps->vui.chroma_sample_loc_type_bottom_field );
    sprintf(buffer, " timing_info_present_flag : %d \n", sps->vui.timing_info_present_flag );
      sprintf(buffer, "   num_units_in_tick : %d \n", sps->vui.num_units_in_tick );
      sprintf(buffer, "   time_scale : %d \n", sps->vui.time_scale );
      sprintf(buffer, "   fixed_frame_rate_flag : %d \n", sps->vui.fixed_frame_rate_flag );
    sprintf(buffer, " nal_hrd_parameters_present_flag : %d \n", sps->vui.nal_hrd_parameters_present_flag );
    sprintf(buffer, " vcl_hrd_parameters_present_flag : %d \n", sps->vui.vcl_hrd_parameters_present_flag );
      sprintf(buffer, "   low_delay_hrd_flag : %d \n", sps->vui.low_delay_hrd_flag );
    sprintf(buffer, " pic_struct_present_flag : %d \n", sps->vui.pic_struct_present_flag );
    sprintf(buffer, " bitstream_restriction_flag : %d \n", sps->vui.bitstream_restriction_flag );
      sprintf(buffer, "   motion_vectors_over_pic_boundaries_flag : %d \n", sps->vui.motion_vectors_over_pic_boundaries_flag );
      sprintf(buffer, "   max_bytes_per_pic_denom : %d \n", sps->vui.max_bytes_per_pic_denom );
      sprintf(buffer, "   max_bits_per_mb_denom : %d \n", sps->vui.max_bits_per_mb_denom );
      sprintf(buffer, "   log2_max_mv_length_horizontal : %d \n", sps->vui.log2_max_mv_length_horizontal );
      sprintf(buffer, "   log2_max_mv_length_vertical : %d \n", sps->vui.log2_max_mv_length_vertical );
      sprintf(buffer, "   num_reorder_frames : %d \n", sps->vui.num_reorder_frames );
      sprintf(buffer, "   max_dec_frame_buffering : %d \n", sps->vui.max_dec_frame_buffering );

    sprintf(buffer, "=== HRD ===\n");
    sprintf(buffer, " cpb_cnt_minus1 : %d \n", sps->hrd.cpb_cnt_minus1 );
    sprintf(buffer, " bit_rate_scale : %d \n", sps->hrd.bit_rate_scale );
    sprintf(buffer, " cpb_size_scale : %d \n", sps->hrd.cpb_size_scale );
    int SchedSelIdx;
    for( SchedSelIdx = 0; SchedSelIdx <= sps->hrd.cpb_cnt_minus1; SchedSelIdx++ )
    {
        sprintf(buffer, "   bit_rate_value_minus1[%d] : %d \n", SchedSelIdx, sps->hrd.bit_rate_value_minus1[SchedSelIdx] ); // up to cpb_cnt_minus1, which is <= 31
        sprintf(buffer, "   cpb_size_value_minus1[%d] : %d \n", SchedSelIdx, sps->hrd.cpb_size_value_minus1[SchedSelIdx] );
        sprintf(buffer, "   cbr_flag[%d] : %d \n", SchedSelIdx, sps->hrd.cbr_flag[SchedSelIdx] );
    }
    sprintf(buffer, " initial_cpb_removal_delay_length_minus1 : %d \n", sps->hrd.initial_cpb_removal_delay_length_minus1 );
    sprintf(buffer, " cpb_removal_delay_length_minus1 : %d \n", sps->hrd.cpb_removal_delay_length_minus1 );
    sprintf(buffer, " dpb_output_delay_length_minus1 : %d \n", sps->hrd.dpb_output_delay_length_minus1 );
    sprintf(buffer, " time_offset_length : %d \n", sps->hrd.time_offset_length );
}


void print_pps(char *buffer, pps_t* pps)
{
    sprintf(buffer, "======= PPS =======\n");
    sprintf(buffer, " pic_parameter_set_id : %d \n", pps->pic_parameter_set_id );
    sprintf(buffer, " seq_parameter_set_id : %d \n", pps->seq_parameter_set_id );
    sprintf(buffer, " entropy_coding_mode_flag : %d \n", pps->entropy_coding_mode_flag );
    sprintf(buffer, " pic_order_present_flag : %d \n", pps->pic_order_present_flag );
    sprintf(buffer, " num_slice_groups_minus1 : %d \n", pps->num_slice_groups_minus1 );
    sprintf(buffer, " slice_group_map_type : %d \n", pps->slice_group_map_type );
    //  int run_length_minus1[8]; // up to num_slice_groups_minus1, which is <= 7 in Baseline and Extended, 0 otheriwse
    //  int top_left[8];
    //  int bottom_right[8];
    //  int slice_group_change_direction_flag;
    //  int slice_group_change_rate_minus1;
    //  int pic_size_in_map_units_minus1;
    //  int slice_group_id[256]; // FIXME what size?
    sprintf(buffer, " num_ref_idx_l0_active_minus1 : %d \n", pps->num_ref_idx_l0_active_minus1 );
    sprintf(buffer, " num_ref_idx_l1_active_minus1 : %d \n", pps->num_ref_idx_l1_active_minus1 );
    sprintf(buffer, " weighted_pred_flag : %d \n", pps->weighted_pred_flag );
    sprintf(buffer, " weighted_bipred_idc : %d \n", pps->weighted_bipred_idc );
    sprintf(buffer, " pic_init_qp_minus26 : %d \n", pps->pic_init_qp_minus26 );
    sprintf(buffer, " pic_init_qs_minus26 : %d \n", pps->pic_init_qs_minus26 );
    sprintf(buffer, " chroma_qp_index_offset : %d \n", pps->chroma_qp_index_offset );
    sprintf(buffer, " deblocking_filter_control_present_flag : %d \n", pps->deblocking_filter_control_present_flag );
    sprintf(buffer, " constrained_intra_pred_flag : %d \n", pps->constrained_intra_pred_flag );
    sprintf(buffer, " redundant_pic_cnt_present_flag : %d \n", pps->redundant_pic_cnt_present_flag );
    sprintf(buffer, " transform_8x8_mode_flag : %d \n", pps->transform_8x8_mode_flag );
    sprintf(buffer, " pic_scaling_matrix_present_flag : %d \n", pps->pic_scaling_matrix_present_flag );
    //  int pic_scaling_list_present_flag[8];
    //  void* ScalingList4x4[6];
    //  int UseDefaultScalingMatrix4x4Flag[6];
    //  void* ScalingList8x8[2];
    //  int UseDefaultScalingMatrix8x8Flag[2];
    sprintf(buffer, " second_chroma_qp_index_offset : %d \n", pps->second_chroma_qp_index_offset );
}

void print_slice_header(char *buffer, slice_header_t* sh)
{
    sprintf(buffer, "======= Slice Header =======\n");
    sprintf(buffer, " first_mb_in_slice : %d \n", sh->first_mb_in_slice );
    const char* slice_type_name;
    switch(sh->slice_type)
    {
    case SH_SLICE_TYPE_P :       slice_type_name = "P slice"; break;
    case SH_SLICE_TYPE_B :       slice_type_name = "B slice"; break;
    case SH_SLICE_TYPE_I :       slice_type_name = "I slice"; break;
    case SH_SLICE_TYPE_SP :      slice_type_name = "SP slice"; break;
    case SH_SLICE_TYPE_SI :      slice_type_name = "SI slice"; break;
    case SH_SLICE_TYPE_P_ONLY :  slice_type_name = "P slice only"; break;
    case SH_SLICE_TYPE_B_ONLY :  slice_type_name = "B slice only"; break;
    case SH_SLICE_TYPE_I_ONLY :  slice_type_name = "I slice only"; break;
    case SH_SLICE_TYPE_SP_ONLY : slice_type_name = "SP slice only"; break;
    case SH_SLICE_TYPE_SI_ONLY : slice_type_name = "SI slice only"; break;
    default :                    slice_type_name = "Unknown"; break;
    }
    sprintf(buffer, " slice_type : %d ( %s ) \n", sh->slice_type, slice_type_name );

    sprintf(buffer, " pic_parameter_set_id : %d \n", sh->pic_parameter_set_id );
    sprintf(buffer, " frame_num : %d \n", sh->frame_num );
    sprintf(buffer, " field_pic_flag : %d \n", sh->field_pic_flag );
      sprintf(buffer, " bottom_field_flag : %d \n", sh->bottom_field_flag );
    sprintf(buffer, " idr_pic_id : %d \n", sh->idr_pic_id );
    sprintf(buffer, " pic_order_cnt_lsb : %d \n", sh->pic_order_cnt_lsb );
    sprintf(buffer, " delta_pic_order_cnt_bottom : %d \n", sh->delta_pic_order_cnt_bottom );
    // int delta_pic_order_cnt[ 2 ];
    sprintf(buffer, " redundant_pic_cnt : %d \n", sh->redundant_pic_cnt );
    sprintf(buffer, " direct_spatial_mv_pred_flag : %d \n", sh->direct_spatial_mv_pred_flag );
    sprintf(buffer, " num_ref_idx_active_override_flag : %d \n", sh->num_ref_idx_active_override_flag );
    sprintf(buffer, " num_ref_idx_l0_active_minus1 : %d \n", sh->num_ref_idx_l0_active_minus1 );
    sprintf(buffer, " num_ref_idx_l1_active_minus1 : %d \n", sh->num_ref_idx_l1_active_minus1 );
    sprintf(buffer, " cabac_init_idc : %d \n", sh->cabac_init_idc );
    sprintf(buffer, " slice_qp_delta : %d \n", sh->slice_qp_delta );
    sprintf(buffer, " sp_for_switch_flag : %d \n", sh->sp_for_switch_flag );
    sprintf(buffer, " slice_qs_delta : %d \n", sh->slice_qs_delta );
    sprintf(buffer, " disable_deblocking_filter_idc : %d \n", sh->disable_deblocking_filter_idc );
    sprintf(buffer, " slice_alpha_c0_offset_div2 : %d \n", sh->slice_alpha_c0_offset_div2 );
    sprintf(buffer, " slice_beta_offset_div2 : %d \n", sh->slice_beta_offset_div2 );
    sprintf(buffer, " slice_group_change_cycle : %d \n", sh->slice_group_change_cycle );

    sprintf(buffer, "=== Prediction Weight Table ===\n");
        sprintf(buffer, " luma_log2_weight_denom : %d \n", sh->pwt.luma_log2_weight_denom );
        sprintf(buffer, " chroma_log2_weight_denom : %d \n", sh->pwt.chroma_log2_weight_denom );
     //   sprintf(buffer, " luma_weight_l0_flag : %d \n", sh->pwt.luma_weight_l0_flag );
        // int luma_weight_l0[64];
        // int luma_offset_l0[64];
    //    sprintf(buffer, " chroma_weight_l0_flag : %d \n", sh->pwt.chroma_weight_l0_flag );
        // int chroma_weight_l0[64][2];
        // int chroma_offset_l0[64][2];
     //   sprintf(buffer, " luma_weight_l1_flag : %d \n", sh->pwt.luma_weight_l1_flag );
        // int luma_weight_l1[64];
        // int luma_offset_l1[64];
    //    sprintf(buffer, " chroma_weight_l1_flag : %d \n", sh->pwt.chroma_weight_l1_flag );
        // int chroma_weight_l1[64][2];
        // int chroma_offset_l1[64][2];

    sprintf(buffer, "=== Ref Pic List Reordering ===\n");
        sprintf(buffer, " ref_pic_list_reordering_flag_l0 : %d \n", sh->rplr.ref_pic_list_reordering_flag_l0 );
        sprintf(buffer, " ref_pic_list_reordering_flag_l1 : %d \n", sh->rplr.ref_pic_list_reordering_flag_l1 );
        // int reordering_of_pic_nums_idc;
        // int abs_diff_pic_num_minus1;
        // int long_term_pic_num;

    sprintf(buffer, "=== Decoded Ref Pic Marking ===\n");
        sprintf(buffer, " no_output_of_prior_pics_flag : %d \n", sh->drpm.no_output_of_prior_pics_flag );
        sprintf(buffer, " long_term_reference_flag : %d \n", sh->drpm.long_term_reference_flag );
        sprintf(buffer, " adaptive_ref_pic_marking_mode_flag : %d \n", sh->drpm.adaptive_ref_pic_marking_mode_flag );
        // int memory_management_control_operation;
        // int difference_of_pic_nums_minus1;
        // int long_term_pic_num;
        // int long_term_frame_idx;
        // int max_long_term_frame_idx_plus1;

}

void print_aud(char *buffer, aud_t* aud)
{
    sprintf(buffer, "======= Access Unit Delimiter =======\n");
    const char* primary_pic_type_name;
    switch (aud->primary_pic_type)
    {
    case AUD_PRIMARY_PIC_TYPE_I :       primary_pic_type_name = "I"; break;
    case AUD_PRIMARY_PIC_TYPE_IP :      primary_pic_type_name = "I, P"; break;
    case AUD_PRIMARY_PIC_TYPE_IPB :     primary_pic_type_name = "I, P, B"; break;
    case AUD_PRIMARY_PIC_TYPE_SI :      primary_pic_type_name = "SI"; break;
    case AUD_PRIMARY_PIC_TYPE_SISP :    primary_pic_type_name = "SI, SP"; break;
    case AUD_PRIMARY_PIC_TYPE_ISI :     primary_pic_type_name = "I, SI"; break;
    case AUD_PRIMARY_PIC_TYPE_ISIPSP :  primary_pic_type_name = "I, SI, P, SP"; break;
    case AUD_PRIMARY_PIC_TYPE_ISIPSPB : primary_pic_type_name = "I, SI, P, SP, B"; break;
    default : primary_pic_type_name = "Unknown"; break;
    }
    sprintf(buffer, " primary_pic_type : %d ( %s ) \n", aud->primary_pic_type, primary_pic_type_name );
}

void print_seis(char *buffer, h264_stream_t* h)
{
    sei_t** seis = h->seis;
    int num_seis = h->num_seis;

    sprintf(buffer, "======= SEI =======\n");
    const char* sei_type_name;
    int i;
    for (i = 0; i < num_seis; i++)
    {
        sei_t* s = seis[i];
        switch(s->payloadType)
        {
        case SEI_TYPE_BUFFERING_PERIOD :          sei_type_name = "Buffering period"; break;
        case SEI_TYPE_PIC_TIMING :                sei_type_name = "Pic timing"; break;
        case SEI_TYPE_PAN_SCAN_RECT :             sei_type_name = "Pan scan rect"; break;
        case SEI_TYPE_FILLER_PAYLOAD :            sei_type_name = "Filler payload"; break;
        case SEI_TYPE_USER_DATA_REGISTERED_ITU_T_T35 : sei_type_name = "User data registered ITU-T T35"; break;
        case SEI_TYPE_USER_DATA_UNREGISTERED :    sei_type_name = "User data unregistered"; break;
        case SEI_TYPE_RECOVERY_POINT :            sei_type_name = "Recovery point"; break;
        case SEI_TYPE_DEC_REF_PIC_MARKING_REPETITION : sei_type_name = "Dec ref pic marking repetition"; break;
        case SEI_TYPE_SPARE_PIC :                 sei_type_name = "Spare pic"; break;
        case SEI_TYPE_SCENE_INFO :                sei_type_name = "Scene info"; break;
        case SEI_TYPE_SUB_SEQ_INFO :              sei_type_name = "Sub seq info"; break;
        case SEI_TYPE_SUB_SEQ_LAYER_CHARACTERISTICS : sei_type_name = "Sub seq layer characteristics"; break;
        case SEI_TYPE_SUB_SEQ_CHARACTERISTICS :   sei_type_name = "Sub seq characteristics"; break;
        case SEI_TYPE_FULL_FRAME_FREEZE :         sei_type_name = "Full frame freeze"; break;
        case SEI_TYPE_FULL_FRAME_FREEZE_RELEASE : sei_type_name = "Full frame freeze release"; break;
        case SEI_TYPE_FULL_FRAME_SNAPSHOT :       sei_type_name = "Full frame snapshot"; break;
        case SEI_TYPE_PROGRESSIVE_REFINEMENT_SEGMENT_START : sei_type_name = "Progressive refinement segment start"; break;
        case SEI_TYPE_PROGRESSIVE_REFINEMENT_SEGMENT_END : sei_type_name = "Progressive refinement segment end"; break;
        case SEI_TYPE_MOTION_CONSTRAINED_SLICE_GROUP_SET : sei_type_name = "Motion constrained slice group set"; break;
        case SEI_TYPE_FILM_GRAIN_CHARACTERISTICS : sei_type_name = "Film grain characteristics"; break;
        case SEI_TYPE_DEBLOCKING_FILTER_DISPLAY_PREFERENCE : sei_type_name = "Deblocking filter display preference"; break;
        case SEI_TYPE_STEREO_VIDEO_INFO :         sei_type_name = "Stereo video info"; break;
        default: sei_type_name = "Unknown"; break;
        }
        sprintf(buffer, "=== %s ===\n", sei_type_name);
        sprintf(buffer, " payloadType : %d \n", s->payloadType );
        sprintf(buffer, " payloadSize : %d \n", s->payloadSize );

        sprintf(buffer, " payload : " );
        print_bytes(buffer, s->payload, s->payloadSize);
    }
}

/**
 Print the contents of a NAL unit to standard output.
 The NAL which is printed out has a type determined by nal and data which comes from other fields within h depending on its type.
 @param[in]      h          the stream object
 @param[in]      nal        the nal unit
 */
void print_nal(char *buffer, h264_stream_t* h, nal_t* nal)
{
    sprintf(buffer, "==================== NAL ====================\n");
    sprintf(buffer, " forbidden_zero_bit : %d \n", nal->forbidden_zero_bit );
    sprintf(buffer, " nal_ref_idc : %d \n", nal->nal_ref_idc );
    // TODO make into subroutine
    const char* nal_unit_type_name;
    switch (nal->nal_unit_type)
    {
    case  NAL_UNIT_TYPE_UNSPECIFIED :                   nal_unit_type_name = "Unspecified"; break;
    case  NAL_UNIT_TYPE_CODED_SLICE_NON_IDR :           nal_unit_type_name = "Coded slice of a non-IDR picture"; break;
    case  NAL_UNIT_TYPE_CODED_SLICE_DATA_PARTITION_A :  nal_unit_type_name = "Coded slice data partition A"; break;
    case  NAL_UNIT_TYPE_CODED_SLICE_DATA_PARTITION_B :  nal_unit_type_name = "Coded slice data partition B"; break;
    case  NAL_UNIT_TYPE_CODED_SLICE_DATA_PARTITION_C :  nal_unit_type_name = "Coded slice data partition C"; break;
    case  NAL_UNIT_TYPE_CODED_SLICE_IDR :               nal_unit_type_name = "Coded slice of an IDR picture"; break;
    case  NAL_UNIT_TYPE_SEI :                           nal_unit_type_name = "Supplemental enhancement information (SEI)"; break;
    case  NAL_UNIT_TYPE_SPS :                           nal_unit_type_name = "Sequence parameter set"; break;
    case  NAL_UNIT_TYPE_PPS :                           nal_unit_type_name = "Picture parameter set"; break;
    case  NAL_UNIT_TYPE_AUD :                           nal_unit_type_name = "Access unit delimiter"; break;
    case  NAL_UNIT_TYPE_END_OF_SEQUENCE :               nal_unit_type_name = "End of sequence"; break;
    case  NAL_UNIT_TYPE_END_OF_STREAM :                 nal_unit_type_name = "End of stream"; break;
    case  NAL_UNIT_TYPE_FILLER :                        nal_unit_type_name = "Filler data"; break;
    case  NAL_UNIT_TYPE_SPS_EXT :                       nal_unit_type_name = "Sequence parameter set extension"; break;
        // 14..18    // Reserved
    case  NAL_UNIT_TYPE_CODED_SLICE_AUX :               nal_unit_type_name = "Coded slice of an auxiliary coded picture without partitioning"; break;
        // 20..23    // Reserved
        // 24..31    // Unspecified
    default :                                           nal_unit_type_name = "Unknown"; break;
    }
    sprintf(buffer, " nal_unit_type : %d ( %s ) \n", nal->nal_unit_type, nal_unit_type_name );

    if( nal->nal_unit_type == NAL_UNIT_TYPE_CODED_SLICE_NON_IDR) { print_slice_header(buffer, h->sh); }
    else if( nal->nal_unit_type == NAL_UNIT_TYPE_CODED_SLICE_IDR) { print_slice_header(buffer, h->sh); }
    else if( nal->nal_unit_type == NAL_UNIT_TYPE_SPS) { print_sps(buffer, h->sps); }
    else if( nal->nal_unit_type == NAL_UNIT_TYPE_PPS) { print_pps(buffer, h->pps); }
    else if( nal->nal_unit_type == NAL_UNIT_TYPE_AUD) { print_aud(buffer, h->aud); }
    else if( nal->nal_unit_type == NAL_UNIT_TYPE_SEI) { print_seis(buffer, h ); }
}

void print_bytes(char *buffer, uint8_t* buf, int len)
{
    int i;
    for (i = 0; i < len; i++)
    {
        sprintf(buffer, "%02X ", buf[i]);
        if ((i+1) % 16 == 0) { printf ("\n"); }
    }
    sprintf(buffer, "\n");
}

H264NALListModel::H264NALListModel(const QString &filename, QObject *parent)
    :QAbstractTableModel(parent),
      m_filename(filename),
      m_fileBuffer(),
      m_nalList()
{
    load();
    parse();
}

void H264NALListModel::load()
{
    QFile file(m_filename);
    if (file.open(QFile::ReadOnly))
    {
        m_fileBuffer = file.readAll();
        file.close();
    }
}

void H264NALListModel::parse()
{
    int offset = 0;
    while(offset < m_fileBuffer.size())
    {
        int nal_start = 0;
        int nal_end = 0;
        find_nal_unit((uint8_t*)(m_fileBuffer.data() + offset), m_fileBuffer.size(), &nal_start, &nal_end);

        if (nal_end - nal_start > 0)
        {
            h264_stream_t *h = h264_new();
            read_nal_unit(h, &(((uint8_t*)m_fileBuffer.data())[nal_start + offset]), nal_end - nal_start);
            //print_nal(h, h->nal);
            m_nalList.push_back(h);
        }

        offset += nal_end;
    }
}

int H264NALListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_nalList.size();
}

int H264NALListModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 3;
}

QVariant H264NALListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation == Qt::Vertical)
    {
        if (role == Qt::DisplayRole)
        {
            return QString("%1").arg(section);
        }
        else
        {
            return QVariant();
        }
    }
    else if(orientation == Qt::Horizontal)
    {
        if (role == Qt::DisplayRole)
        {
            switch(section)
            {
            case 0:
                return QString("Unit Type");
            case 1:
                return QString("Reference Idc");
            case 2:
                return QString("Size");
            }
        }
    }
    return QVariant();
}

QVariant H264NALListModel::data(const QModelIndex &index, int role) const
{
    h264_stream_t *h = m_nalList[index.row()];

    if(role == Qt::UserRole)
    {
        QByteArray temp(50000, 0);

        print_nal(temp.data(), h, h->nal);
        qDebug() << temp;

        QString result = QString::fromLocal8Bit(temp);
        return result;
    }

    if (index.column() == 0)
    {
        switch(role)
        {
        case Qt::DisplayRole:
        {
            switch(h->nal->nal_unit_type)
            {
            case NAL_UNIT_TYPE_UNSPECIFIED:
                return QString("Unspecified");
            case NAL_UNIT_TYPE_CODED_SLICE_NON_IDR:
                return QString("Coded slice of a non-IDR picture");
            case NAL_UNIT_TYPE_CODED_SLICE_DATA_PARTITION_A:
                return QString("Coded slice data partition A");
            case NAL_UNIT_TYPE_CODED_SLICE_DATA_PARTITION_B:
                return QString("Coded slice data partition B");
            case NAL_UNIT_TYPE_CODED_SLICE_DATA_PARTITION_C:
                return QString("Coded slice data partition C");
            case NAL_UNIT_TYPE_CODED_SLICE_IDR:
                return QString("Coded slice of an IDR picture");
            case NAL_UNIT_TYPE_SEI:
                return QString("Supplemental enhancement information (SEI)");
            case NAL_UNIT_TYPE_SPS:
                return QString("Sequence parameter set");
            case NAL_UNIT_TYPE_PPS:
                return QString("Picture parameter set");
            case NAL_UNIT_TYPE_AUD:
                return QString("Access unit delimiter");
            case NAL_UNIT_TYPE_END_OF_SEQUENCE:
                return QString("End of sequence");
            case NAL_UNIT_TYPE_END_OF_STREAM:
                return QString("End of stream");
            case NAL_UNIT_TYPE_FILLER:
                return QString("Filler data");
            case NAL_UNIT_TYPE_SPS_EXT:
                return QString("Sequence parameter set extension");
            case NAL_UNIT_TYPE_CODED_SLICE_AUX:
                return QString("Coded slice of an auxiliary coded picture without partitioning");
            default:
                return QString("Unknown unit type");
            }
        }
        case Qt::DecorationRole:
        {
            switch(h->nal->nal_unit_type)
            {
            case NAL_UNIT_TYPE_UNSPECIFIED:
                return QColor(163, 30, 57);
            case NAL_UNIT_TYPE_CODED_SLICE_NON_IDR:
                return QColor(214, 228, 225);
            case NAL_UNIT_TYPE_CODED_SLICE_DATA_PARTITION_A:
                return QColor(191, 207, 204);
            case NAL_UNIT_TYPE_CODED_SLICE_DATA_PARTITION_B:
                return QColor(157, 178, 177);
            case NAL_UNIT_TYPE_CODED_SLICE_DATA_PARTITION_C:
                return QColor(140, 156, 154);
            case NAL_UNIT_TYPE_CODED_SLICE_IDR:
                return QColor(72, 92, 90);
            case NAL_UNIT_TYPE_SEI:
                return QColor(255, 99, 77);
            case NAL_UNIT_TYPE_SPS:
                return QColor(253, 237, 208);
            case NAL_UNIT_TYPE_PPS:
                return QColor(188, 241, 237);
            case NAL_UNIT_TYPE_AUD:
                return QColor(238, 186, 76);
            case NAL_UNIT_TYPE_END_OF_SEQUENCE:
                return QColor(227, 73, 59);
            case NAL_UNIT_TYPE_END_OF_STREAM:
                return QColor(35, 181, 175);
            case NAL_UNIT_TYPE_FILLER:
                return QColor(58, 58, 60);
            case NAL_UNIT_TYPE_SPS_EXT:
                return QColor(253, 121, 91);
            case NAL_UNIT_TYPE_CODED_SLICE_AUX:
                return QColor(169, 221, 217);
            default:
                return QColor(163, 30, 57);
            }
        }

        default:
            return QVariant();
        }
    }
    else if (index.column() == 1)
    {
        switch(role)
        {
        case Qt::DisplayRole:
        {
            return h->nal->nal_ref_idc;
        }
        }
    }
    else if(index.column() == 2)
    {
        switch(role)
        {
        case Qt::DisplayRole:
        {
            return h->nal->sizeof_parsed;
        }
        }
    }
    return QVariant();
}

H264NALListModel::~H264NALListModel()
{
    foreach(h264_stream_t *h, m_nalList)
    {
        h264_free(h);
    }
}

