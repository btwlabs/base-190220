<?php

/**
 * Get the Node (nee CCK) description of the instagram_photo content type
 *
 * @return array - per node_type_save
 */
function mcn_instagram_type_instagram() {
  $type = array(
    'type' => 'instagram_photo',
    'name' => st('Instagram Photo'),
    'base' => 'node_content',
    'description' => st('Photos to hotlink from Instagram'),
    'help' => st('A moderatable instagram photo. Will usually be generated automatically.'),
    'custom' => TRUE,
    'modified' => FALSE,
    'locked' => TRUE,
    'hast_title' => TRUE,
    'title_label' => 'Title',
  );
  $type = node_type_set_defaults($type);
  return $type;
} // mcn_instagram_type_instagram

/**
 * Add the custom fields to the instagram_photo content type
 *
 * @return array - of arrays per field_create_field and field_create_instance
 */
function mcn_instagram_fields_instagram() {
  $result = array(
    'field_instagram_id' => array(
      'field' => array(
        'field_name' => 'field_instagram_id',
        'type' => 'text',
      ),
      'instance' => array(
        'label' => st('Instagram ID'),
        'description' => st('Unique ID assigned by Instagram'),
        'widget' => array('type' => 'text_textfield'),
      ),
    ), 
    'field_instagram_link' => array(
      'field' => array(
        'field_name' => 'field_instagram_link',
        'type' => 'text',
      ),
      'instance' => array(
        'label' => st('Link'),
        'description' => st('Link to this image on Instagram'),
        'widget' => array('type' => 'text_textfield'),
      ),
    ),
    'field_image_preview' => array(
      'field' => array(
        'field_name' => 'field_image_preview',
        'type' => 'text',
      ),
      'instance' => array(
        'label' => st('Image, Preview'),
        'description' => st('Link to a preview image'),
        'widget' => array('type' => 'text_textfield'),
      ),
    ),
    'field_image_full' => array(
      'field' => array(
        'field_name' => 'field_image_full',
        'type' => 'text',
      ),
      'instance' => array(
        'label' => st('Image, Full'),
        'description' => st('Link to the full-size image'),
        'widget' => array('type' => 'text_textfield'),
      ),
    ),
    'field_tag_comment' => array(
      'field' => array(
        'field_name' => 'field_tag_comment',
        'type' => 'text_long',
      ),
      'instance' => array(
        'label' => st('Comment'),
        'description' => st('This field holds the contents of the comment which tagged this photo.'),
        'widget' => array('type' => 'text_textfield'),
      ),
    ),
    'field_rejected' => array(
      'field' => array(
        'field_name' => 'field_rejected',
        'type' => 'list_integer',
        'settings' => array(
          'allowed_values' => array(
            0 => 'Acceptable',
            1 => 'Reject',
          )
        ),
      ),
      'instance' => array(
        'label' => st('Reject'),
        'description' => st('Reject this image for inappropriate content?'),
        'widget' => array('type' => 'options_onoff'),
      ),
    ),
    'field_winner' => array(
      'field' => array(
        'field_name' => 'field_winner',
        'type' => 'list_integer',
        'settings' => array(
          'allowed_values' => array(
            0 => '',
            1 => 'Winner',
          )
        ),
      ),
      'instance' => array(
        'label' => st('Winner'),
        'description' => st('Declare this picture to be a winner?'),
        'widget' => array('type' => 'optio_onoff'),
      ),
    ),
  );
  return $result;
} // mcn_instagram_field_instagram
