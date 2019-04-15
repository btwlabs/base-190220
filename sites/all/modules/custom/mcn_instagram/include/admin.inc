<?php

/**
 * @file - mcn_instagram admin from functions
 */

/**
 * Generate the admin form for instagram
 *
 * @return array per the drupal forms API
 */
function mcn_instagram_admin() {
  $form = array();
  $form['mcn_instagram_client_id'] = array(
    '#type' => 'textfield',
    '#default_value' => variable_get('mcn_instagram_client_id', ''),
    '#required' => TRUE,
    '#title' => t('Instagram App Client ID'),
    '#description' => t('Log in to instagram.com/developer to set this up.'),
  );
  $form['mcn_instagram_tag'] = array(
    '#type' => 'textfield',
    '#default_value' => implode(' ', variable_get('mcn_instagram_tag', array())),
    '#title' => t('Tag(s)'),
    '#description' => t('Photos with this tag will be pulled from Instagram. Separate multiple tags with spaces.'),
  );
  $form['buttons'] = array(
    'submit' => array(
      '#type' => 'submit',
      '#value' => t('Save'),
    ),
    'import' => array(
      '#type' => 'submit',
      '#value' => t('Save and Import Photos'),
    ),
  );
  return $form;
} // mcn_instagram_admin

/**
 * Validate function for mcn_instagram_admin form
 *
 * Verify that they entered useful Instagram API data
 */
function mcn_instagram_admin_validate($form, &$form_state) {
  $tags_str = strtolower($form_state['values']['mcn_instagram_tag']);
  if (preg_match('/[^a-z0-9_ ]/', $tags_str)) {
    form_set_error(
      'mcn_instagram_tag',
      t("Only letters, numbers, and underscores are permitted in hashtags. (Yes, we are ethnocentric. This is 'murica!)")
    );
  } else {
    $tags = explode(' ', $tags_str);
    $client_id = $form_state['values']['mcn_instagram_client_id'];
    $tag = reset($tags);
    $tag_info = mcn_instagram_query("tags/$tag", 'GET', array('client_id' => $client_id));
    if (isset($tag_info->meta->error_message)) {
      form_set_error('mcn_instagram_client_id', t('Error authenticating to Instagram: "@s"', array('@s' => $tag_info->meta->error_message)));
    }
  }
} // mcn_instagram_admin_validate

/**
 * Submit function for mcn_instagram_admin form
 *
 * @param $form array - per drupal forms api
 * @param &$form_state array - per drupal forms api
 */
function mcn_instagram_admin_submit($form, &$form_state) {
  $tags_str = strtolower($form_state['values']['mcn_instagram_tag']);
  $tags = explode(' ', $tags_str);
  variable_set('mcn_instagram_tag', $tags);
  variable_set('mcn_instagram_client_id', $form_state['values']['mcn_instagram_client_id']);
  drupal_set_message(t('Settings saved'));
  if ($form_state['values']['op'] == $form['buttons']['import']['#value']) {
    module_load_include('inc', 'mcn_instagram', 'include/fetch');
    $counts = mcn_instagram_update_subscription();
    $message = t('New images were imported for these tags:') . '<ul>';
    foreach ($counts AS $tag => $count) {
      if ($count > 0) {
        $message .= "<li>$tag => $count</li>";
      }
    }
    $message .= '</ul>';
    drupal_set_message($message);
  } // if import button hit
} // mcn_instagram_admin_submit
