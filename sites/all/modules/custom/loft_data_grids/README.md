##Summary
A module wrapper integrating [Loft Data Grids](https://github.com/aklump/loft_data_grids) with Drupal.

##Installation
1. Download and unzip this module into your modules directory.
1. Download [Loft Data Grids](https://github.com/aklump/loft_data_grids) to `sites/all/libraries`; unzip and rename to `loft_data_grids`.

## Important!  Please read regarding dependencies!
_The Loft Data Grids PHP Library (for which this Drupal module is a wrapper) uses several external libraries to provide the different export types.  That library assumes you will use Composer to install these dependencies.  This Drupal module makes an exception if you want to use certain Drupal library module(s) instead, such as [PHPExcel][phpexcel].  It is the author's recommendation that you still go the route of installing these dependencies using Composer if you are able, as it gives you the widest selection of export types.  However if you are only concerned about Excel exporting and you want to skip the Composer complexity use option B._

### Option A: Using Composer
2. In shell, `cd` to `sites/all/libraries/loft_data_grids`
3. Continue with installation instructions at [Loft Data Grids](https://github.com/aklump/loft_data_grids#installation).

### Option B: Skipping Composer
2. If you are NOT familiar with [Composer](http://getcomposer.org) or you would RATHER use the [PHPExcel][phpexcel] Drupal module, you should install and enable that module before enabling this one.
3. Be aware that some of the Export types are not supported by Drupal if you skip Composer.

_In the event that you install dependencies with both Composer AND you have the PHPExcel Drupal module enabled, this module will pull the PHPExcel library source code from the composer location, rather than the drupal PHPExcel module folder._

##Installation (cont.)
1. Now go to Administer > Site Building > Modules and enable this module.
3. Visit `admin/reports/status` and confirm the library is being detected and loaded correctly.


##Usage
To use any of the classes in [Loft Data Grids](https://github.com/aklump/loft_data_grids) call the following two functions below to instantiate objects:

    <?php
    $data = loft_data_grids_export_data();
    $data->add('first', 'Aaron');
    $data->add('last', 'Klump');
    $output = loft_data_grids_exporter($data, 'CSVExporter')->export();
    ?>
    
Refer to the library for more info.  It also contains Doxygene docs.


##Contact
* **In the Loft Studios**
* Aaron Klump - Developer
* PO Box 29294 Bellingham, WA 98228-1294
* _aim_: theloft101
* _skype_: intheloftstudios
* _d.o_: aklump
* <http://www.InTheLoftStudios.com>

[phpexcel]: https://drupal.org/project/phpexcel