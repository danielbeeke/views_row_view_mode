<?php

/**
 * Implements hook_views_plugins().
 */
function views_row_view_mode_views_plugins() {
  $plugins = array(
    'style' => array(
      // Default settings for all style plugins.
      'views_row_view_mode' => array(
        'title' => t('Views row view mode'),
        'help' => t('Displays rows one after another.'),
        'handler' => 'views_plugin_style_views_row_view_mode',
        'theme' => 'views_row_view_mode',
        'uses row plugin' => TRUE,
        'uses row class' => TRUE,
        'uses grouping' => TRUE,
        'uses options' => TRUE,
        'type' => 'normal',
        'help topic' => 'style-unformatted',
      ),
    ),
  );

  return $plugins;
}

/**
 * @file
 * Contains the default style plugin.
 */

/**
 * Default style plugin to render rows one after another with no
 * decorations.
 *
 * @ingroup views_style_plugins
 */
class views_plugin_style_views_row_view_mode extends views_plugin_style_default {
  function options_form(&$form, &$form_state) {
    $form['every_row_numbers'] = array(
      '#title' => t('Add views row number classes'),
      '#description' => t('If you add 4, 5 every-4 and every-5 classes will be added to the views row.'),
      '#type' => 'textfield',
      '#default_value' => $this->options['every_row_numbers'],
    );
  }
}
