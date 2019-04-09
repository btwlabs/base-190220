<?php

/**
 * @file
 * Extra pages for the Facebook Wall module.
 */

/**
 * Facebook wall post content fetcher.
 */
function facebook_wall_display_posts() {
  // FB Graph API CURL Calls request.
  $requestFields = "fields=picture,type,actions,id,link,story,created_time,message,name,caption,description,source,likes{id,name},comments{from,message,created_time,fan_count}";
  $api_url = 'https://graph.facebook.com/' . FB_API_VER . '/' . FB_PAGE_NAME . '/feed?' . $requestFields . '&access_token=' . FB_ACCESS_TOKEN . '&limit=' . (int) variable_get('facebook_wall_post_limit', 10);

  // HTML Contains FB current wall post.
  $html = _facebook_wall_theme_html_content($api_url);

  if (FB_ACCESS_TOKEN == '') {
    return;
  }
  elseif ($html != FALSE) {
    $form['facebook_wall'] = array(
      '#markup' => $html,
    );

    if (variable_get('facebook_wall_older_post_button') == 1) {
      // This will be append by wth an updated wall post value.
      $form['div_append_next_wall_post'] = array(
        '#markup' => '',
        '#prefix' => '<div style="float:left; width: ' . variable_get('facebook_wall_width_size') . 'px;"  id="div_append_next_wall_post">',
        '#suffix' => '</div>',
      );
      $form['facebook_wall_next_wall_post'] = array(
        '#type' => 'button',
        '#value' => t('Get older Posts'),
        '#ajax' => array(
          'callback' => '_facebook_wall_ajax_next_wall_post',
          'wrapper' => 'div_append_next_wall_post',
          'method' => 'append',
        ),
        '#prefix' => '<div style="clear:both; margin-top:10px;">',
        '#suffix' => '</div>',
      );
    }
    return $form;
  }
  else {
    $message = t("Facebook wall post is not available ! This may caused due to user's content privacy policy.");
    watchdog('facebook wall', $message, array(), WATCHDOG_DEBUG);
    if (variable_get('facebook_wall_message_show', 1)) {
      drupal_set_message($message, 'warning');
    }
  }
}

/**
 * Ajax call to get older FB wall posts.
 */
function _facebook_wall_ajax_next_wall_post($form, $form_state) {
  $api_url = variable_get('facebook_wall_post_pagging_next');

  $html = _facebook_wall_theme_html_content($api_url);
  if ($html != FALSE) {
    return $html;
  }

  return 'Not able to get older posts';
}
