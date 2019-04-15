<?php

/**
 * @file - mcn_admin image moderation form
 */

/**
 * Generate the Instagram photo moderation form
 *
 * @return array per the Drupal forms API
 */
function mcn_instagram_moderate() {
  $form = array();
  $form['photos'] = array(
    '#tree' => TRUE,
    '#type' => 'fieldset',
  );
  $query = db_select('node', 'n')
    ->fields('n', array('nid'));
  $query->join('field_data_field_rejected', 'r', 'r.entity_id = n.nid');
  $query->condition('r.field_rejected_value', 0, '=')
    ->condition('n.status', 0, '=');
  $q_res = $query->execute();
  $no_photos = TRUE;
  while ($nid = $q_res->fetchField()) {
    $node = node_load($nid);
    $form['photos'][$node->nid] = array(
      '#type' => 'radios',
      '#options' => array(
        NODE_NOT_PUBLISHED => t('Reject'),
        NODE_PUBLISHED => t('Accept'),
      ),
      '#default_value' => 1,
      '#title' => t($node->title),
      '#prefix' => theme('mcn_instagram_img', array('node' => $node, 'mode' => MCN_INSTAGRAM_IMG_PREVIEW)),
    );
    $no_photos = FALSE;
  } // while fetching db results
  if ($no_photos) {
    $form['photos']['message'] = array(
      '#type' => 'markup',
      '#markup' => '<div class="mcn_instagram-message messages status">'
        . t('No new photos found')
        . '</div>',
    );
  }
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit (and load new photos if applicable)'),
  );
  return $form;
} // mcn_instagram_moderate

/**
 * Submit function for mcn_instagram_moderate form
 *
 * Publish/reject photos
 *
 * @param $form array per the Drupal forms API
 * @param &$form_state array per the Drupal forms API
 */
function mcn_instagram_moderate_submit($form, &$form_state) {
  foreach ($form['photos'] AS $nid => $val) {
    if (is_int($nid)) {
      $accepted = $form_state['values']['photos'][$nid];
      $node = node_load($nid);
      if ($accepted == NODE_PUBLISHED) {
        $node->status = 1;
      } else {
        $node->field_rejected[LANGUAGE_NONE][0]['value'] = 1;
      }
      node_save($node);
    }
  } // foreach photo
} // mcn_instagram_moderate_submit
