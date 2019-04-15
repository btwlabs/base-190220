<?php

/**
 * @file - cron functions for mcn_instagram module
 */
/**
 * Verify that all the images we have cached right now still exist
 */
function mcn_instagram_cleanup() {
  // short circuit
  $client_id = variable_get('mcn_instagram_client_id', '');
  if (!$client_id) { return; }

  //Get our list of existing photos
  $queue = variable_get('mcn_instagram_verification_queue', array());
  if (empty($queue)) {
    $query = db_select('field_data_field_instagram_id', 'fdfiiv')
      ->fields('fdfiiv', array('field_instagram_id_value', 'entity_id'))
      ->execute();
    while($fields = $query->fetchAssoc()) {
      $queue[$fields['entity_id']] = $fields['field_instagram_id_value'];
    }  // while fetching db results
  } // if empty(queue)

  $i = 0;
  $nids = array_keys($queue);
  while ($i < 100 && !empty($queue)) {
    $iid = array_pop($queue);
    $nid = array_pop($nids);
    if (!mcn_instagram_check_validity($iid)) {
      node_delete($nid);
    }
    $i++;
  } // while iterating through queue
  variable_set('mcn_instagram_verificiation_queue', $queue);
} // mcn_instagram_cleanup

/**
 * Verify that an instagram ID is still valid
 *
 * @param $iid string - instagram photo ID
 * @return boolean - is the photo still valid?
 */
function mcn_instagram_check_validity($iid) {
  $resource = "media/$iid";
  $instagram = mcn_instagram_query($resource);
  $result = isset($instagram->data->tags);
  if ($result) {
    $our_tags = variable_get('mcn_instagram_tag', '');
    $lower_tags = array_map('strtolower', $instagram->data->tags);
    $intersect = array_intersect($our_tags, $lower_tags);
    $result = !empty($intersect);
  }
  return $result;
} // mcn_instagram_check_validity
