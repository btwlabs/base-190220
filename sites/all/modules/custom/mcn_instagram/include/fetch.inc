<?php

/**
 * @file - Retreive new data from Instagram
 */

/**
 * Pull in new data from instagram
 *
 * @return array - keys are tags; values are count of images imported
 */
function mcn_instagram_update_subscription() {
  $result = array();
  $tags = variable_get('mcn_instagram_tag', 'mcncontesttest');
  $latest = variable_get('mcn_instagram_latest', array());
  foreach ($tags AS $tag) {
    $resource = "tags/$tag/media/recent";
    $get_opts = array();
    if (isset($latest[$tag])) {
      $get_opts['min_tag_id'] = $latest[$tag];
    }
    $api_res = mcn_instagram_query($resource, 'GET', $get_opts);
    $count = 0;
    if ($api_res->meta->code == 200) {
      foreach ($api_res->data AS $datum) {
        $link = trim($datum->link);
        $low_res = trim($datum->images->thumbnail->url);
        $high_res = trim($datum->images->standard_resolution->url);
        $comments = array($datum->caption) + $datum->comments->data;
        $id = trim($datum->id);
        $username = trim($datum->user->username);
        //make sure it doesn't already exist
        $unique_photo = !db_select('field_data_field_instagram_id', 'id')
          ->fields('id', array('entity_id'))
          ->condition('field_instagram_id_value', $id, '=')
          ->execute()
          ->fetchField();
        $valid_photo = $unique_photo && $link && $low_res && $high_res;
        if ($valid_photo) {
          $comment = mcn_instagram_get_comment($comments, $tag);
          $node = mcn_instagram_new_photo($id, $link, $low_res, $high_res, $comment, $username);
          $count++;
        } // if valid_photo
      } // foreach datum in api_res->data
      $latest[$tag] = trim($api_res->pagination->min_tag_id);
      $result[$tag] = $count;
    } // if 200 returned from API call
  } // foreach tag in tags
  variable_set('mcn_instagram_latest', $latest);
  return $result;
} // mcn_instagram_update_subscription

/**
 * Get a single comment containing a tag
 *
 * @param $comments object list of comments on this photo (per the IG API)
 * @param $tag string the tag to look for
 * @return string a comment from the list
 */
function mcn_instagram_get_comment($comments, $tag) {
  $result = '';
  $tag = '#' . strtolower($tag);
  foreach ($comments AS $comment) {
    if (strpos(strtolower($comment->text), $tag) !== FALSE) {
      $result = drupal_convert_to_utf8(trim($comment->text), 'ISO-8859-1');
      break;
    } // tag found
  } //foreach comment in comments
  return $result;
} // mcn_instagram_get_comment

/**
 * Create a new instagram_photo node
 *
 * @param $id string -  instagram ID number
 * @param $link string - URL of the photo's description on instagram
 * @param $low_res string - URL of a low res version of the photo
 * @param $high_res string - URL of a high res version of the photo
 * @param $comment string - the comment to attach to this photo
 * @param $username string - username of the photo uploader
 * @return object - an Instagram Photo node
 */
function mcn_instagram_new_photo($id, $link, $low_res, $high_res, $comment, $username) {
  $node = new stdClass();
  $node->type = 'instagram_photo';
  $node->title = check_plain($username);
  $node->status = NODE_NOT_PUBLISHED;
  $node->field_instagram_id = array(LANGUAGE_NONE => array(0 => array('value' => $id)));
  $node->field_instagram_link = array(LANGUAGE_NONE => array(0 => array('value' => $link)));
  $node->field_image_preview = array(LANGUAGE_NONE => array(0 => array('value' => $low_res)));
  $node->field_image_full = array(LANGUAGE_NONE => array(0 => array('value' => $high_res)));
  $node->field_rejected = array(LANGUAGE_NONE => array(0 => array('value' => 0)));
  $node->field_winner = array(LANGUAGE_NONE => array(0 => array('value' => 0)));
  $node->field_tag_comment = array(LANGUAGE_NONE => array(0 => array('value' => $comment)));
  node_save($node);

  return $node;
} // mcn_instagram_new_photo
