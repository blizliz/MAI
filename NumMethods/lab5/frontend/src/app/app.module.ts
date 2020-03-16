import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';
import { MatSidenavModule } from '@angular/material/sidenav';
import {MatCardModule, MatListModule} from '@angular/material';
import { MathJaxModule } from 'ngx-mathjax';

import { AppComponent } from './app.component';
import { LeftBarComponent } from './left-bar/left-bar.component';
import { BrowserAnimationsModule } from '@angular/platform-browser/animations';
import { Lab1Component } from './lab1/lab1.component';
import { AppRoutingModule } from './app-routing.module';
import {RouterModule} from '@angular/router';
import { Lab2Component } from './lab2/lab2.component';
import { Lab3Component } from './lab3/lab3.component';


@NgModule({
  declarations: [
    AppComponent,
    LeftBarComponent,
    Lab1Component,
    Lab2Component,
    Lab3Component
  ],
  imports: [
    BrowserModule,
    BrowserAnimationsModule,
    MatSidenavModule,
    AppRoutingModule,
    RouterModule,
    MatListModule,
    MathJaxModule.forRoot({
      version: '2.7.5',
      config: 'TeX-AMS_HTML',
      hostname: 'cdnjs.cloudflare.com'
    }),
    MatCardModule,
  ],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule { }
