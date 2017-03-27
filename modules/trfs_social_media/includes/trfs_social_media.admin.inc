<?php

/*
 * Implements hook_form().
 */
function trfs_social_media_settings_form($form){

  $trfs_social_media_settings = variable_get('trfs_social_media_settings');

  $form['twitter_left'] = array(
    '#type' => 'fieldset',
    '#title' => t('Twitter Left'),
    '#collapsible' => TRUE, // Added
    '#collapsed' => FALSE,  // Added
  );

  $form['twitter_left']['oauth_access_token_left'] = array(
    '#title' => 'OAuth Access Token',
    '#type' => 'textfield',
    '#default_value' => $trfs_social_media_settings['oauth_access_token_left'],
    '#description' => '"Access token" on https://apps.twitter.com.',
    '#required' => 1,
    '#maxlength' => 255,
  );
  $form['twitter_left']['oauth_access_token_secret_left'] = array(
    '#title' => 'Access token secret',
    '#type' => 'textfield',
    '#default_value' => $trfs_social_media_settings['oauth_access_token_secret_left'],
    '#description' => '"Access token secret" on https://apps.twitter.com',
    '#required' => 1,
    '#maxlength' => 255,
  );
  $form['twitter_left']['consumer_key_left'] = array(
    '#title' => 'API key',
    '#type' => 'textfield',
    '#default_value' => $trfs_social_media_settings['consumer_key_left'],
    '#description' => '"API key" on https://apps.twitter.com',
    '#required' => 1,
    '#maxlength' => 255,
  );
  $form['twitter_left']['consumer_secret_left'] = array(
    '#title' => 'API secret',
    '#type' => 'textfield',
    '#default_value' => $trfs_social_media_settings['consumer_secret_left'],
    '#description' => '"API secret" on https://apps.twitter.com',
    '#required' => 1,
    '#maxlength' => 255,
  );
  $form['twitter_left']['user_id_left'] = array(
    '#title' => 'User id',
    '#type' => 'textfield',
    '#default_value' => $trfs_social_media_settings['user_id_left'],
    '#description' => 'User id (http://gettwitterid.com/)',
    '#required' => 1,
    '#maxlength' => 255,
  );
  $form['twitter_left']['screen_name_left'] = array(
    '#title' => 'Twitter handle',
    '#type' => 'textfield',
    '#default_value' => $trfs_social_media_settings['screen_name_left'],
    '#description' => 'Twitter handle',
    '#required' => 1,
    '#maxlength' => 255,
  );
  $form['twitter_left']['count_left'] = array(
    '#title' => 'Tweet Count',
    '#type' => 'textfield',
    '#default_value' => $trfs_social_media_settings['count_left'],
    '#description' => 'The number of tweets to pull out',
    '#required' => 1,
    '#maxlength' => 255,
  );
  $form['twitter_right'] = array(
    '#type' => 'fieldset',
    '#title' => t('Twitter Right'),
    '#collapsible' => TRUE, // Added
    '#collapsed' => FALSE,  // Added
  );

  $form['twitter_right']['oauth_access_token_right'] = array(
    '#title' => 'OAuth Access Token',
    '#type' => 'textfield',
    '#default_value' => $trfs_social_media_settings['oauth_access_token_right'],
    '#description' => '"Access token" on https://apps.twitter.com.',
    '#required' => 1,
    '#maxlength' => 255,
  );
  $form['twitter_right']['oauth_access_token_secret_right'] = array(
    '#title' => 'Access token secret',
    '#type' => 'textfield',
    '#default_value' => $trfs_social_media_settings['oauth_access_token_secret_right'],
    '#description' => '"Access token secret" on https://apps.twitter.com',
    '#required' => 1,
    '#maxlength' => 255,
  );
  $form['twitter_right']['consumer_key_right'] = array(
    '#title' => 'API key',
    '#type' => 'textfield',
    '#default_value' => $trfs_social_media_settings['consumer_key_right'],
    '#description' => '"API key" on https://apps.twitter.com',
    '#required' => 1,
    '#maxlength' => 255,
  );
  $form['twitter_right']['consumer_secret_right'] = array(
    '#title' => 'API secret',
    '#type' => 'textfield',
    '#default_value' => $trfs_social_media_settings['consumer_secret_right'],
    '#description' => '"API secret" on https://apps.twitter.com',
    '#required' => 1,
    '#maxlength' => 255,
  );
  $form['twitter_right']['user_id_right'] = array(
    '#title' => 'User id',
    '#type' => 'textfield',
    '#default_value' => $trfs_social_media_settings['user_id_right'],
    '#description' => 'User id (http://gettwitterid.com/)',
    '#required' => 1,
    '#maxlength' => 255,
  );
  $form['twitter_right']['screen_name_right'] = array(
    '#title' => 'Twitter handle',
    '#type' => 'textfield',
    '#default_value' => $trfs_social_media_settings['screen_name_right'],
    '#description' => 'Twitter handle',
    '#required' => 1,
    '#maxlength' => 255,
  );
  $form['twitter_right']['count_right'] = array(
    '#title' => 'Tweet Count',
    '#type' => 'textfield',
    '#default_value' => $trfs_social_media_settings['count_right'],
    '#description' => 'The number of tweets to pull out',
    '#required' => 1,
    '#maxlength' => 255,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
  return $form;
}

/*
 * Implements hook_form_submit().
 */
function trfs_social_media_settings_form_submit($form, &$form_state){

  variable_set('trfs_social_media_settings', $form_state['values']);

  drupal_set_message('Configurations Saved');
}
