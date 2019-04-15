<?php

/**
 * @file - template preprocess functions for the mcn_instagram module
 */

/**
 * Template preprocess for theme(mcn_instagram_img)
 *
 * @param &$variables array - per drupal theme api
 */
function template_preprocess_mcn_instagram_img(&$variables) {
  $node = $variables['node'];
  $variables['img'] = $variables['mode'] == MCN_INSTAGRAM_IMG_PREVIEW
    ? $node->field_image_preview[LANGUAGE_NONE][0]['value']
    : $node->field_image_full[LANGUAGE_NONE][0]['value'];
  $variables['url'] = url(
    $node->field_instagram_link[LANGUAGE_NONE][0]['value'],
    array('absolute' => TRUE)
  );
  $variables['title'] = check_plain($node->title);
  $variables['comment'] = check_plain($node->field_tag_comment[LANGUAGE_NONE][0]['value']);
} // template_preprocess_mcn_instagram_img
