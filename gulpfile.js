var gulp = require('gulp'),
    gutil = require('gulp-util'),
    sass = require('gulp-sass'),
    uglify = require('gulp-uglify'),
    sourcemaps = require('gulp-sourcemaps'),
    babel = require('gulp-babel'),
    concat = require('gulp-concat'),
    browserify = require('gulp-browserify');
    babelify = require('babelify');

// Paths
var jsSources = [
      'sites/all/themes/custom/rarefew/js/*.js',
      'sites/all/themes/custom/rarefew/js/**/*.js',
      '!sites/all/themes/custom/rarefew/js/min/*.js',
      '!sites/all/themes/custom/rarefew/js/react_src/*.js',
      '!sites/all/themes/custom/rarefew/js/react_src/**/*.js',
      '!sites/all/themes/custom/rarefew/js/react_builds/*.js',
      '!sites/all/themes/custom/rarefew/js/*.min.js'
    ],
    sassSources = ['sites/all/themes/custom/rarefew/sass/*.scss',
      'sites/all/themes/custom/rarefew/sass/**/*.scss',
    ],
    scripts_dest = 'sites/all/themes/custom/rarefew/js/min/',
    sass_dest = 'sites/all/themes/custom/rarefew/css/';

gulp.task('sass', function() {
  gulp.src(sassSources)
  .pipe(sourcemaps.init())
  .pipe(sass({outputStyle: 'compressed'}).on('error', sass.logError))
  .pipe(sourcemaps.write('./maps'))
  .pipe(gulp.dest(sass_dest));
});

gulp.task('js', function() {
  gulp.src(jsSources)
  .pipe(sourcemaps.init())
  .pipe(babel({
      presets: ['es2015']
    }).on('error', gutil.log))
  .pipe(uglify().on('error', gutil.log)) // notice the error event here
  .pipe(concat('script.min.js'))
  .pipe(sourcemaps.write('./maps'))
  .pipe(gulp.dest(scripts_dest))
});

gulp.task('watch', function() {
  gulp.watch(jsSources, ['js']);
  gulp.watch( srcReact , ['jsreact']);
  gulp.watch(sassSources, ['sass']);
});

gulp.task('default', ['watch', 'js', 'sass']);
