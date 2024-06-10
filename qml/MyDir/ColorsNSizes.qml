pragma Singleton

import QtQuick

Item {

    QtObject{
        id: _Themes
        readonly property var _Dark: ["Dark" , "#dbe2ef", "#7881ae", "#aab2cf", "#848cb5"]
        readonly property var _Light: ["Light" , "#caf0f8", "#0077b6", "#00b4d8", "#90e0ef"]
    }
    property var _CurrentTheme: _Themes._Dark
    property var themes: _Themes


    readonly property string _ThemeName : _CurrentTheme[0]
    readonly property string _PrimaryPurple: _CurrentTheme[1]
    readonly property string _PrimaryBlue: _CurrentTheme[2]
    readonly property string _SecondaryBlue: _CurrentTheme[3]
    readonly property string _PrimaryGray: _CurrentTheme[4]


    readonly property string _AttentionColor: "red"

    readonly property string _LightBlue: "#dbe2ef"
    readonly property string _LightPurple: "#7881ae"
    readonly property string _PowderBlue: "#aab2cf"
    readonly property string _CoolGray: "#848cb5"
    readonly property int _SideButtonHeight: 140
    readonly property int _SideButtonWidth: 400
    readonly property int _BigFont: 52
    readonly property int _MediumFont: 32
    readonly property int _SmallFont: 16

    readonly property double _IconHolderScale : 0.25
    readonly property double _TextFieldScale : 1.2
    readonly property double _ButtonScaleX : 2
    readonly property double _ButtonScaleY : 18.5

    readonly property double _SubjectScaleX : 1.1
    readonly property double _SubjectScaleY : 3.5

    readonly property double _MenuButtonScaleX : 7

    readonly property double _SideButtonScaleY : 8

    readonly property double _SliderScaleX : 4
    readonly property double _SliderScaleY : 20

    readonly property double _BreakerScaleY : 8




}
