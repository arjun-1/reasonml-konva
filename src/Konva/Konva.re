module Line = {
  [@bs.module "react-konva"] [@react.component]
  external make:
    (
      ~points: array(float),
      ~bezier: bool=?,
      ~fill: string=?,
      ~stroke: string=?,
      ~strokeWidth: float=?
    ) =>
    React.element =
    "Line";
};

module Stage = {
  [@bs.module "react-konva"] [@react.component]
  external make: (~width: int, ~height: int, ~children: React.element=?) => React.element =
    "Stage";
};

module Layer = {
  [@bs.module "react-konva"] [@react.component]
  external make: (~children: React.element=?) => React.element = "Layer";
};

module Rect = {
  [@bs.module "react-konva"] [@react.component]
  external make:
    (~x: float, ~y: float, ~width: float, ~height: float, ~fill: string=?, ~shadowBlur: float=?) =>
    React.element =
    "Rect";
};

module Shape = {
  type t;
  [@bs.send] external x: t => float = "x";
  [@bs.send] external y: t => float = "y";
};

module Node = {
  type t;
};

module Event = {
  type dragEvent = ReactEvent.Mouse.t;

  [@bs.deriving abstract]
  type konvaEvent('e) = {
    target: Shape.t,
    evt: 'e,
    currentTarget: Node.t,
    cancelBubble: bool,
    [@bs.optional]
    child: Node.t,
  };
};

module Circle = {
  [@bs.module "react-konva"] [@react.component]
  external make:
    (
      ~radius: float,
      ~x: float,
      ~y: float,
      ~fill: string=?,
      ~stroke: string=?,
      ~strokeWidth: float=?,
      ~draggable: bool=?,
      ~onDragStart: Event.konvaEvent(Event.dragEvent) => unit=?,
      ~onDragMove: Event.konvaEvent(Event.dragEvent) => unit=?,
      ~onDragEnd: Event.konvaEvent(Event.dragEvent) => unit=?
    ) =>
    React.element =
    "Circle";
};
