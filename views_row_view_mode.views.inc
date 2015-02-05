<?php
/**
 * @file
 * Implements all the views hooks for views row mode.
 */

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
    parent::options_form($form, $form_state);

    $form['every_row_numbers'] = array(
      '#title' => t('Add views row number classes'),
      '#description' => t('If you add 4, 5 every-4 and every-5 classes will be added to the views row.'),
      '#type' => 'textfield',
      '#default_value' => $this->options['every_row_numbers'],
    );
  }

  /**
   * Render the grouping sets.
   *
   * Plugins may override this method if they wish some other way of handling
   * grouping.
   *
   * @param $sets
   *   Array containing the grouping sets to render.
   * @param $level
   *   Integer indicating the hierarchical level of the grouping.
   *
   * @return string
   *   Rendered output of given grouping sets.
   */
  function render_grouping_sets($sets, $level = 0) {
    $output = '';
    foreach ($sets as $set) {
      $set_index = 0;

      $row = reset($set['rows']);
      // Render as a grouping set.
      if (is_array($row) && isset($row['group'])) {
        $output .= theme(views_theme_functions('views_view_grouping', $this->view, $this->display),
          array(
            'view' => $this->view,
            'grouping' => $this->options['grouping'][$level],
            'grouping_level' => $level,
            'rows' => $set['rows'],
            'title' => $set['group'])
        );
      }
      // Render as a record set.
      else {
        if ($this->uses_row_plugin()) {
          foreach ($set['rows'] as $index => $row) {
            $this->view->row_index = $set_index;
            // sdpm($this->row_plugin);
            $set['rows'][$index] = $this->row_plugin->render($row);
            $set_index++;
          }
        }

        $output .= theme($this->theme_functions(),
          array(
            'view' => $this->view,
            'options' => $this->options,
            'grouping_level' => $level,
            'rows' => $set['rows'],
            'title' => $set['group'])
        );
      }
    }
    unset($this->view->row_index);
    return $output;
  }
}
