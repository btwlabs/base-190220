<?php

/**
 * Query the Instagram API
 *
 * @param $resource string - path to query
 * @param $method string - GET|POST|DELETE
 * @param $get_post array - GET/POST variables
 * @return object - decoded result returned from Instagram
 */
function mcn_instagram_query($resource, $method = 'GET', $get_post = array()) {
  $c = curl_init();
  $url = "https://api.instagram.com/v1/$resource";
  if (!isset($get_post['client_id'])) {
    $get_post['client_id'] = variable_get('mcn_instagram_client_id', '');
  }
  if ($method == 'GET') {
    if (!empty($get_post)) {
      $url .= '?' . drupal_http_build_query($get_post);
    }
  } else if ($method == 'POST') {
    curl_setopt($c, CURLOPT_POSTFIELDS, $get_post);
    curl_setopt($c, CURLOPT_POST, TRUE);
  } else {
    if (!empty($get_post)) {
      curl_setopt($c, CURLOPT_POSTFIELDS, $get_post);
    }
    curl_setopt($c, CURLOPT_CUSTOMREQUEST, $method);
  }
  curl_setopt($c, CURLOPT_URL, $url);
  curl_setopt($c, CURLOPT_RETURNTRANSFER, 1);
  curl_setopt($c, CURLOPT_SSL_VERIFYPEER, FALSE);
  $c_res = curl_exec($c);
  $result = json_decode($c_res);
  return $result;
} // mcn_instagram_query
