# 1.1 왜 리액트인가?

리액트는 대용량 플젝에서 데이터의 값이 바뀌면 변경되어야 하는 부분에 하나하나 적용하기가 힘들어져서 페북 개발자들이 고안해 낸 라이브러리.

이런 문제점을 반영해 기존 뷰를 그냥 날려버리고 새로운 뷰를 대체하는 방식으로 짜여진 것.

리액트는 MVC, MVW 등의 아키텍쳐를 가진 여타 라이브러리들과는 달리 오직 V(View)만 고려함

## 리액트 이해

### render() 함수

-   역할: 컴포넌트가 어떻게 생겼는지 정의
-   반환: 뷰가 어떻게 생겼고 어떻게 작동하는 지에 대한 정보를 담은 객체

render 함수를 실행하면 그 내부에 있는 컴포넌트들도 재귀적으로 렌더링

작업들이 끝나면 html 마크업을 만들고 ⇒ 실제 페이지의 DOM 요소에 주입

### reconciliation(조화) 과정

아까 말했듯이, 데이터에 변화가 생기면 리액트는 그 뷰를 아예 갈아끼어버림(~~손절)~~

이건 render 함수를 재호출하는 방식으로 진행됨.

‼️ 그런데 전에 호출했던 render가 반환했던 결과랑 지금 render 호출하는 결과를 비교해서 변화가 있는 친구들만 갈아낌(그림 1-6 참고).

⇒ 즉 최소한의 연산ㅇㅇ

# 1.2 리액트의 특징

## Virtual DOM

### DOM이란?

= Document Object Model

객체로 문서 구조를 표현하는 방법, XML이나 html로 작성됨

웹 브라우저는 DOM을 활용해서 객체에 js나 css를 적용함.

DOM은 트리 형태임, 그래서 어떤 특정 노드를 찾거나 수정하거나 삭제하거나 등 할 수 있음.

DOM은 동적 UI에 최적화되어 있지 않음 → 따라서 브라우저 단에서 DOM에 변화가 일어나면 웹 브라우저가 CSS를 재 연산, 레이아웃 재구성, 페이지 리페인트함.

동적인 웹에서는 ⇒ 느릴 수 밖에 없음.

### Virtual DOM

따라서 DOM을 최소한으로 조작하면 개선 가능 == Virtual DOM

리액트에서는 추상화한 js 객체를 사용해서 Virtual DOM으로 이용함.

⏲️ 리액트에서 데이터가 변해 웹 브라우저에서 실제 DOM에 업데이트할 때 밟는 3가지 절차 ⏲️

1. 데이터를 업데이트하면 전체 UI에서 Virtual DOM에 re-render
2. 이전 Virtual DOM에 있던 내용과 현재 내용을 비교
3. 바뀐 부분만 실제 DOM에 적용함

그래서 아까 [그림 1-6]의 바뀐 DOM 트리가 그 VIrtual DOM 트리로 확인하는 것임.

### 오해

react라고 해서 무조건 빠른 건 아님.

리액트 메뉴얼에도 "지속적으로 변화하는 대규모 애플리케이션"에 적용하는 것을 권장한다고 함.

static page에는 오히려 react를 적용하지 않는 게 더 낫다고 함

### ++ 기타

리액트는 라이브러리이므로, 다른 라이브러리들이랑 섞어서 쓸 수 있음.

흥미로운 점은 다른 프레임워크에 섞어서 쓸 수 있다는 것임.. WoW..😯😯

# 1.3 작업 환경 설정

-생략-
